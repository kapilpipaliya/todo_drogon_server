#pragma once
namespace openproj {
namespace models {
namespace Queries::Filters::Strategies {
  namespace Numeric {
//     void included(base) {
//      base.supported_operators = ["=", "!", ">=", "<=", "!*", "*"]
//      base.default_operator = "="
//    }

     void validate() {
//      validate_values_all_numeric
    }

//    private:

//     virtual void numeric_class()  = 0;

//     virtual void error_message()  = 0;

//     void validate_values_all_numeric() {
//      if ( operator && operator.requires_value? && values.any? { |value| !numeric?(value) }) {
//        errors.add(:values, I18n.t("activerecord.errors.messages.#{error_message}"))
//      }
//    }

//     void numeric?(str) {
//      if ( Object.send(numeric_class.to_s, str)) { true ;}
//    rescue ArgumentError
//      false
//    }
  }
}
}
}