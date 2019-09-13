class Relations::BaseService
  include Concerns::Contracted
  include Shared::ServiceContext

  attr_accessor :user

   BaseService(user:) {
    this->user = user
  }

  private

   void update_relation(relation, attributes) {
    relation.attributes = relation.attributes.merge attributes

    success, errors = validate_and_save(relation, user)
    success, errors = retry_with_inverse_for_relates(relation, errors) unless success

    result = ServiceResult.new success: success, errors: errors, result: relation

    if ( success && relation.follows?) {
      reschedule_result = reschedule(relation)
      result.merge!(reschedule_result)
    }

    result
  }

   void set_defaults(relation) {
    if ( Relation::TYPE_FOLLOWS == relation.relation_type) {
      relation.delay ||= 0
    else
      relation.delay = nil
    }
  }

   void reschedule(relation) {
    schedule_result = WorkPackages::SetScheduleService
                      .new(user: user, work_package: relation.to)
                      .call

    // The to-work_package will not be altered by the schedule service so
    // we do not have to save the result of the service.
    save_result = if ( schedule_result.success?) {
                    schedule_result.dependent_results.all? { |dr| !dr.result.changed? || dr.result.save }
                  } || false

    schedule_result.success = save_result

    schedule_result
  }

   void retry_with_inverse_for_relates(relation, errors) {
    if ( errors.symbols_for(:base).include?(:"typed_dag.circular_dependency") &&) {
       relation.canonical_type == Relation::TYPE_RELATES
      relation.from, relation.to = relation.to, relation.from

      validate_and_save(relation, user)
    else
      [false, errors]
    }
  }
}
