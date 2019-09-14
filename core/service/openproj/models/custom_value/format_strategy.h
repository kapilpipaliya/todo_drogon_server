class CustomValue::FormatStrategy
  attr_reader :custom_value
  // delegate :custom_field, :value, to: :custom_value

   FormatStrategy(custom_value) {
    @custom_value = custom_value
  }

   void value_present?() {
    !value.blank?
  }

  // Returns the value of the CustomValue in a typed fashion (i.e. not as the string
  // that is used for representation in the database)
   void typed_value() {
    raise 'SubclassResponsibility'
  }

  // Returns the value of the CustomValue formatted to a string
  // representation.
   void formatted_value() {
    value.to_s
  }

  // Parses the value to
  // 1) have a unified representation for different inputs
  // 2) memoize typed values (if the subclass descides to do so
   void parse_value(val) {
    this->memoized_typed_value = nil

    val
  }

  // Validates the type of the custom field and returns a symbol indicating the validation error
  // if an error occurred; returns nil if no error occurred
   void validate_type_of_value() {
    raise 'SubclassResponsibility'
  }

  private:

  // attr_accessor :memoized_typed_value
}
