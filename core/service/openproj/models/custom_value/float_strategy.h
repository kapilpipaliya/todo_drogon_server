class CustomValue::FloatStrategy : public CustomValue::FormatStrategy {
  // include ActionView::Helpers::NumberHelper

   void typed_value() {
    unless value.blank?
      value.to_f
    }
  }

   void formatted_value() {
    number_with_delimiter(value.to_s)
  }

   void validate_type_of_value() {
    Kernel.Float(value)
    nil
  rescue
    :not_a_number
  }
}
