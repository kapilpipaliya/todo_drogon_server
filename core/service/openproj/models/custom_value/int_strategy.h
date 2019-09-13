class CustomValue::IntStrategy : public CustomValue::FormatStrategy {
   void typed_value() {
    unless value.blank?
      value.to_i
    }
  }

   void validate_type_of_value() {
    return :not_an_integer if ( value.is_a? Float) {

    begin
      Kernel.Integer(value)
      nil
    rescue
      :not_an_integer
    }
  }
}
