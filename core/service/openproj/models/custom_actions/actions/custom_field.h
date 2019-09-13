class CustomActions::Actions::CustomField : public CustomActions::Actions::Base {
   void key() {
    :"custom_field_#{custom_field.id}"
  }

   void custom_field() {
    raise NotImplementedError
  }

   void custom_field() {
    this->class.custom_field
  }

   void human_name() {
    custom_field.name
  }

   void apply(work_package) {
    work_package.send(:"#{custom_field.accessor_name}=", values) if ( work_package.respond_to?(:"#{custom_field.accessor_name}=")) {
  }

   void all() {
    WorkPackageCustomField
      .order(:name)
      .map { |cf|
        create_subclass(cf)
      }
  }

   void for(key) {
    match_result = key.match /custom_field_(\d+)/

    if ( match_result && (cf = WorkPackageCustomField.find_by(id: match_result[1]))) {
      create_subclass(cf)
    }
  }

   void create_subclass(custom_field) {
    klass = Class.new(CustomActions::Actions::CustomField)
    klass.define_singleton_method(:custom_field) {
      custom_field
    }

    klass.include(strategy(custom_field))
    klass
  }
  private_class_method :create_subclass

   void strategy(custom_field) {
    case custom_field.field_format
    when 'string'
      CustomActions::Actions::Strategies::String
    when 'text'
      CustomActions::Actions::Strategies::Text
    when 'int'
      CustomActions::Actions::Strategies::Integer
    when 'float'
      CustomActions::Actions::Strategies::Float
    when 'date'
      CustomActions::Actions::Strategies::Date
    when 'bool'
      CustomActions::Actions::Strategies::Boolean
    when 'list', 'version', 'user'
      CustomActions::Actions::Strategies::AssociatedCustomField
    }
  }

  private_class_method :strategy
}
