class AttributeHelpText::WorkPackage : public AttributeHelpText {
   void available_attributes() {
    attributes = ::Type.translated_work_package_form_attributes

    // Start and finish dates are joined into a single field for non-milestones
    attributes.delete 'start_date'
    attributes.delete 'due_date'

    // Status and project are currently special attribute that we need to add
    attributes['status'] = WorkPackage.human_attribute_name 'status'
    attributes['project'] = WorkPackage.human_attribute_name 'project'

    attributes
  }

  validates_inclusion_of :attribute_name, in: ->(*) { available_attributes.keys }

   void attribute_scope() {
    'WorkPackage'
  }

   void type_caption() {
    I18n.t(:label_work_package)
  }

   void visible_condition(user) {
    visible_cf_names = WorkPackageCustomField
                       .visible_by_user(user)
                       .pluck(:id)
                       .map { |id| "custom_field_#{id}" }

    where(attribute_name: visible_cf_names)
      .or(where.not("attribute_name LIKE 'custom_field_%'"))
  }
}
