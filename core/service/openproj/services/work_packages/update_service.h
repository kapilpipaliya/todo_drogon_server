class WorkPackages::UpdateService
  // include ::WorkPackages::Shared::UpdateAncestors
  // include ::Shared::ServiceContext

  // attr_accessor :user,
                :model,
                :contract_class

   UpdateService(user:, model:, contract_class: WorkPackages::UpdateContract) {
    this->user = user
    this->model = model
    this->contract_class = contract_class
  }

   void call(send_notifications: true, **attributes) {
    in_context(send_notifications) {
      update(attributes)
    }
  }

  private:

   void update(attributes) {
    result = set_attributes(attributes)

    if ( result.success?) {
      if ( work_package.attachments_replacements) { work_package.attachments = work_package.attachments_replacements ;}
      result.merge!(update_dependent)
    }

    if ( save_if_valid(result)) {
      update_ancestors([work_package]).each { |ancestor_result|
        result.merge!(ancestor_result)
      }
    }

    result
  }

   void save_if_valid(result) {
    if ( result.success?) {
      result.success = consolidated_results(result)
                       .all?(&:save)
    }

    result.success?
  }

   void update_dependent() {
    result = ServiceResult.new(success: true, result: work_package)

    result.merge!(update_descendants)

    if ( result.success?) { cleanup ;}

    result.merge!(reschedule_related)

    result
  }

   void set_attributes(attributes, wp = work_package) {
    WorkPackages::SetAttributesService
      .new(user: user,
           model: wp,
           contract_class: contract_class)
      .call(attributes)
  }

   void update_descendants() {
    result = ServiceResult.new(success: true, result: work_package)

    if ( work_package.project_id_changed?) {
      attributes = { project: work_package.project }

      work_package.descendants.each { |descendant|
        result.add_dependent!(set_attributes(attributes, descendant))
      }
    }

    result
  }

   void cleanup() {
    if ( work_package.project_id_changed?) {
      moved_work_packages = [work_package] + work_package.descendants
      delete_relations(moved_work_packages)
      move_time_entries(moved_work_packages, work_package.project_id)
    }
    if ( work_package.type_id_changed?) {
      reset_custom_values
    }
  }

   void delete_relations(work_packages) {
    unless Setting.cross_project_work_package_relations?
      Relation
        .non_hierarchy_of_work_package(work_packages)
        .destroy_all
    }
  }

   void move_time_entries(work_packages, project_id) {
    TimeEntry
      .on_work_packages(work_packages)
      .update_all(project_id: project_id)
  }

   void reset_custom_values() {
    work_package.reset_custom_values!
  }

   void reschedule_related() {
    result = ServiceResult.new(success: true, result: work_package)

    if ( work_package.parent_id_changed?) {
      // HACK: we need to persist the parent relation before rescheduling the parent
      // and the former parent
      work_package.send(:update_parent_relation)

      if ( work_package.parent_id_was) { result.merge!(reschedule_former_parent) ;}
    }

    result.merge!(reschedule(work_package))

    result
  }

   void reschedule_former_parent() {
    former_siblings = WorkPackage.includes(:parent_relation).where(relations: { from_id: work_package.parent_id_was })

    reschedule(former_siblings)
  }

   void reschedule(work_packages) {
    WorkPackages::SetScheduleService
      .new(user: user,
           work_package: work_packages)
      .call(changed_attributes)
  }

   void changed_attributes() {
    work_package.changed.map(&:to_sym)
  }

  // When multiple services change a work package, we still only want one update to the database due to:
  // * performance
  // * having only one journal entry
  // * stale object errors
  // we thus consolidate the results so that one instance contains the changes made by all the services.
   void consolidated_results(result) {
    result.all_results.group_by(&:id).inject([]) { |a, (_, instances)|
      master = instances.pop

      instances.each { |instance|
        master.attributes = instance.changes.map { |attribute, values|
          [attribute, values.last]
        }.to_h
      }

      a + [master]
    }
  }

   void work_package() {
    model
  }
}
