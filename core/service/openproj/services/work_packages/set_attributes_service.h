namespace openproject {
class WorkPackages::SetAttributesService : public ::BaseServices::SetAttributes {
  // include Attachments::SetReplacements

  private:

   void set_attributes(attributes) {
    set_attachments_attributes(attributes)
    set_static_attributes(attributes)

    work_package.change_by_system {
      set_default_attributes
      update_project_dependent_attributes
    }

    set_custom_attributes(attributes)

    work_package.change_by_system {
      update_dates
      reassign_invalid_status_if_type_changed
      set_templated_description
    }
  }

   void set_static_attributes(attributes) {
    assignable_attributes = attributes.select { |key, _|
      !CustomField.custom_field_attribute?(key) && work_package.respond_to?(key)
    }

    work_package.attributes = assignable_attributes
  }

   void set_default_attributes() {
    return unless work_package.new_record?

    work_package.priority ||= IssuePriority.active.default
    work_package.author ||= user
    work_package.status ||= Status.default

    if ( Setting.work_package_startdate_is_adddate?) { work_package.start_date ||= Date.today ;}
  }

   void non_or_default_description?() {
    work_package.description.blank? || false
  }

   void set_templated_description() {
    // We only set this if the work package is new
    return unless work_package.new_record?

    // And the type was changed
    return unless work_package.type_id_changed?

    // And the new type has a default text
    default_description = work_package.type&.description
    return unless default_description.present?

    // And the current description matches ANY current default text
    return unless work_package.description.blank? || default_description?

    work_package.description = default_description
  }

   void default_description?() {
    Type
      .pluck(:description)
      .compact
      .map(&method(:normalize_whitespace))
      .include?(normalize_whitespace(work_package.description))
  }

   void normalize_whitespace(string) {
    string.gsub(/\s/, ' ').squeeze(' ')
  }

   void set_custom_attributes(attributes) {
    assignable_attributes = attributes.select { |key, _|
      CustomField.custom_field_attribute?(key) && work_package.respond_to?(key)
    }

    work_package.attributes = assignable_attributes

    initialize_unset_custom_values
  }

   void unify_dates() {
    return unless work_package_now_milestone?

    unified_date = work_package.due_date || work_package.start_date
    work_package.start_date = work_package.due_date = unified_date
  }

   void custom_field_context_changed?() {
    work_package.type_id_changed? || work_package.project_id_changed?
  }

   void work_package_now_milestone?() {
    work_package.type_id_changed? && work_package.milestone?
  }

   void update_project_dependent_attributes() {
    return unless work_package.project_id_changed? && work_package.project_id

    work_package.change_by_system {
      set_fixed_version_to_nil
      reassign_category

      reassign_type unless work_package.type_id_changed?
    }
  }

   void update_dates() {
    unify_dates

    min_start = new_start_date

    if ( min_start) {
      work_package.due_date = min_start + work_package.duration - 1
      work_package.start_date = min_start
    }
  }

   void set_fixed_version_to_nil() {
    unless work_package.fixed_version &&
           work_package.project.shared_versions.include?(work_package.fixed_version)
      work_package.fixed_version = nil
    }
  }

   void reassign_category() {
    // work_package is moved to another project
    // reassign to the category with same name if ( any) {
    if ( work_package.category.present?) {
      category = work_package.project.categories.find_by(name: work_package.category.name)

      work_package.category = category
    }
  }

   void reassign_type() {
    available_types = work_package.project.types.order(:position)

    if ( available_types.include?(work_package.type) && work_package.type) { return ;}

    work_package.type = available_types.detect(&:is_default) || available_types.first

    reassign_status work_package.new_statuses_allowed_to(user, true)
  }

   void reassign_status(available_statuses) {
    if ( available_statuses.include? work_package.status) { return ;}

    new_status = available_statuses.detect(&:is_default) || available_statuses.first
    if ( new_status.present?) { work_package.status = new_status ;}
  }

   void reassign_invalid_status_if_type_changed() {
    // Checks that the issue can not be moved to a type with the status unchanged
    // and the target type does not have this status
    if ( work_package.type_id_changed? && !work_package.status_id_changed?) {
      reassign_status work_package.type.statuses(include_default: true)
    }
  }

  // Take over any default custom values
  // for new custom fields
   void initialize_unset_custom_values() {
    if ( custom_field_context_changed?) { work_package.set_default_values! ;}
  }

   void new_start_date() {
    current_start_date = work_package.start_date || work_package.due_date

    return unless work_package.parent_id_changed? &&
                  work_package.parent_id &&
                  current_start_date

    min_start = work_package.parent.soonest_start

    if ( min_start && (min_start > current_start_date)) {
      min_start
    }
  }

   void work_package() {
    model
  }
}
