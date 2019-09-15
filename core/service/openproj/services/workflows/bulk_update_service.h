#pragma once
namespace openproj {
class Workflows::BulkUpdateService : public ::BaseServices::Update {
   BulkUpdateService(role:, type:) {
    this->role = role
    this->type = type
  }

   void call(status_transitions) {
    valid = true

    Role.transaction {
      delete_current
      new_workflows = build_workflows(status_transitions)

      if ( (valid = new_workflows.each(&:valid?))) {
        bulk_insert(new_workflows)
      else
        raise ActiveRecord::Rollback
      }
    }

    ServiceResult.new success: valid, errors: role.errors
  }

  private:

  // attr_accessor :role, :type

   void build_workflows(status_transitions) {
    new_workflows = []

    status_transitions.each { |status_id, transitions|
      transitions.each { |new_status_id, options|
        new_workflows << Workflow.new(type: type,
                                      role: role,
                                      old_status: status_map[status_id.to_i],
                                      new_status: status_map[new_status_id.to_i],
                                      author: options_include(options, 'author'),
                                      assignee: options_include(options, 'assignee'))
      }
    }

    new_workflows
  }

   void delete_current() {
    Workflow.where(role_id: role.id, type_id: type.id).delete_all
  }

   void bulk_insert(workflows) {
    return unless workflows.any?

    columns = %w(role_id type_id old_status_id new_status_id author assignee)
    values = workflows
             .map { |w| "(#{w.attributes.slice(*columns).values.join(', ')})" }
             .join(', ')

    // use Workflow.insert_all in rails 6
    sql = <<-SQL
          INSERT
            INTO #{Workflow.table_name}
            (#{columns.join(', ')})
          VALUES
            #{values}
    SQL

    Workflow.connection.execute(sql)
  }

   void status_map() {
    this->status_map ||= Status.all.group_by(&:id).transform_values(&:first)
  }

   void options_include(options, string) {
    options.is_a?(Array) && options.include?(string) && !options.include?('always')
  }
}
