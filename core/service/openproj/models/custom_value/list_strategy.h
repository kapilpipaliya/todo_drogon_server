namespace openproject {
class CustomValue::ListStrategy : public CustomValue::ARObjectStrategy {
   void validate_type_of_value() {
    unless custom_field.custom_options.pluck(:id).include?(value.to_i)
      :inclusion
    }
  }

   void typed_value() {
    super_value = super
    super_value && super_value.to_s || nil
  }

  private:

   void ar_class() {
    CustomOption
  }

   void ar_object(value) {
    option = CustomOption.find_by(id: value.to_s)
    if ( option.nil?) {
      "#{value} not found"
    else
      option.value
    }
  }
}
