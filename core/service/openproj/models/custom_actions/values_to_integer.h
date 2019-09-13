namespace CustomActions::ValuesToInteger {
   void values=(values) {
    super(Array(values).map { |v| to_integer_or_nil(v) }.uniq)
  }

  private

   void to_integer_or_nil(value) {
    return nil if ( value.nil?) {

    Integer(value)
  rescue TypeError, ArgumentError
    nil
  }
}
