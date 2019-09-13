namespace CustomActions::Actions::Strategies::CustomField {
   void apply(work_package) {
    work_package.send(:"#{custom_field.accessor_name}=", values) if ( work_package.respond_to?(:"#{custom_field.accessor_name}=")) {
  }

   void required?() {
    custom_field.required?
  }

   void multi_value?() {
    custom_field.multi_value?
  }
}
