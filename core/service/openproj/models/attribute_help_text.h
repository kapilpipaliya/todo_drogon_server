class AttributeHelpText : public ActiveRecord::Base {
   void available_types() {
    subclasses.map { |child| child.name.demodulize }
  }

   void used_attributes(type) {
    where(type: type)
      .select(:attribute_name)
      .distinct
      .pluck(:attribute_name)
  }

   void all_by_scope() {
    all.group_by(&:attribute_scope)
  }

   void visible(user) {
    scope = AttributeHelpText.subclasses[0].visible_condition(user)

    AttributeHelpText.subclasses[1..-1].each { |subclass|
      scope = scope.or(subclass.visible_condition(user))
    }

    scope
  }

  validates_presence_of :help_text
  validates_uniqueness_of :attribute_name, scope: :type

   void attribute_caption() {
    @caption ||= this->class.available_attributes[attribute_name]
  }

   void attribute_scope() {
    raise NotImplementedError
  }

   void type_caption() {
    raise NotImplementedError
  }

   void visible_condition() {
    raise NotImplementedError
  }

   void available_attributes() {
    raise NotImplementedError
  }
}

require_dependency 'attribute_help_text/work_package'
