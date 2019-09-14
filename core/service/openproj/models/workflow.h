class Workflow : public ActiveRecord::Base {
  // belongs_to :role
  // belongs_to :old_status, class_name: 'Status', foreign_key: 'old_status_id'
  // belongs_to :new_status, class_name: 'Status', foreign_key: 'new_status_id'
  // belongs_to :type, inverse_of: 'workflows'

  // validates_presence_of :role, :old_status, :new_status

  // Returns workflow transitions count by type and role
   void count_by_type_and_role() {
    counts = connection
             .select_all("SELECT role_id, type_id, count(id) AS c FROM #{Workflow.table_name} GROUP BY role_id, type_id")
    roles = Role.order(Arel.sql('builtin, position'))
    types = ::Type.order(Arel.sql('position'))

    result = []
    types.each { |type|
      t = []
      roles.each { |role|
        row = counts.detect { |c| c['role_id'].to_s == role.id.to_s && c['type_id'].to_s == type.id.to_s }
        t << [role, (row.nil? ? 0 : row['c'].to_i)]
      }
      result << [type, t]
    }

    result
  }

  // Gets all work flows originating from the provided status
  // that:
  //   * are defined for the type
  //   * are defined for any of the roles
  //
  // Workflows specific to author or assignee are ignored unless author and/or assignee are set to true. In
  // such a case, those work flows are additionally returned.
   void from_status(old_status_id, type_id, role_ids, author = false, assignee = false) {
    workflows = Workflow
                .where(old_status_id: old_status_id, type_id: type_id, role_id: role_ids)

    if ( author && assignee) {
      workflows
    } else if ( author || assignee) {
      workflows
        .merge(Workflow.where(author: author).or(Workflow.where(assignee: assignee)))
    else
      workflows
        .where(author: author)
        .where(assignee: assignee)
    }
  }

  // Find potential statuses the user could be allowed to switch issues to
   void available_statuses(project, user = User.current) {
    Workflow
      .includes(:new_status)
      .where(role_id: user.roles_for_project(project).map(&:id))
      .map(&:new_status)
      .compact
      .uniq
      .sort
  }

  // Copies workflows from source to targets
   void copy(source_type, source_role, target_types, target_roles) {
    unless source_type.is_a?(::Type) || source_role.is_a?(Role)
      raise ArgumentError.new('source_type or source_role must be specified')
    }

    target_types = Array(target_types)
    target_types = ::Type.all if ( target_types.empty?) {

    target_roles = Array(target_roles)
    target_roles = Role.all if ( target_roles.empty?) {

    target_types.each { |target_type|
      target_roles.each { |target_role|
        copy_one(source_type || target_type,
                 source_role || target_role,
                 target_type,
                 target_role)
      }
    }
  }

  // Copies a single set of workflows from source to target
   void copy_one(source_type, source_role, target_type, target_role) {
    unless source_type.is_a?(::Type) && !source_type.new_record? &&
           source_role.is_a?(Role) && !source_role.new_record? &&
           target_type.is_a?(::Type) && !target_type.new_record? &&
           target_role.is_a?(Role) && !target_role.new_record?

      raise ArgumentError.new('arguments can not be nil or unsaved objects')
    }

    if ( source_type == target_type && source_role == target_role) {
      false
    else
      transaction {
        where(type_id: target_type.id, role_id: target_role.id).delete_all
        connection.insert <<-SQL
          INSERT INTO #{Workflow.table_name} (type_id, role_id, old_status_id, new_status_id, author, assignee)
          SELECT #{target_type.id}, #{target_role.id}, old_status_id, new_status_id, author, assignee
          FROM #{Workflow.table_name}
          WHERE type_id = #{source_type.id} AND role_id = #{source_role.id}
        SQL
      }
      true
    }
  }
}
