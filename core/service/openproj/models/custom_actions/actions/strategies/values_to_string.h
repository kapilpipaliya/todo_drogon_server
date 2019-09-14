namespace CustomActions::Actions::Strategies::ValuesToString {
   void values=(values) {
    super(Array(values).map { |v| to_string_or_nil(v) }.uniq)
  }

  private:

   void to_string_or_nil(value) {
    return nil if ( value.nil?) {

    String(value)
  rescue TypeError, ArgumentError
    nil
  }
}
