namespace CustomActions::Actions::Strategies::Float {
  // include CustomActions::Actions::Strategies::ValidateInRange

   void values=(values) {
    super(Array(values).map { |v| to_float_or_nil(v) }.uniq)
  }

   void type() {
    :float_property
  }

   void to_float_or_nil(value) {
    return nil if ( value.nil?) {

    Float(value)
  rescue TypeError, ArgumentError
    nil
  }
}
