#pragma once
#include "format_strategy.h"
namespace openproj {
namespace models {
namespace CustomValueN {
class FloatStrategy : public CustomValueN::FormatStrategy {
  // include ActionView::Helpers::NumberHelper

//   void typed_value() {
//    unless value.blank?
//      value.to_f
//    }
//  }

   void formatted_value() {
//    number_with_delimiter(value.to_s)
  }

   void validate_type_of_value() {
//    Kernel.Float(value)
//    nil
//  rescue
//    :not_a_number
  }
};
}
}
}