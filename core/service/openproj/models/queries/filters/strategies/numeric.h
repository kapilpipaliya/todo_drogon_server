namespace Queries::Filters::Strategies {
  namespace Numeric {
     void included(base) {
      base.supported_operators = ['=', '!', '>=', '<=', '!*', '*']
      base.default_operator = '='
    }

     void validate() {
      validate_values_all_numeric
    }

    private:

     void numeric_class() {
      raise NotImplementedError
    }

     void error_message() {
      raise NotImplementedError
    }

     void validate_values_all_numeric() {
      if ( operator && operator.requires_value? && values.any? { |value| !numeric?(value) }) {
        errors.add(:values, I18n.t("activerecord.errors.messages.#{error_message}"))
      }
    }

     void numeric?(str) {
      true if ( Object.send(numeric_class.to_s, str)) {
    rescue ArgumentError
      false
    }
  }
}
