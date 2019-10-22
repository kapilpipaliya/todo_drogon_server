#pragma once
#include "format_strategy.h"
namespace openproj {
namespace models {
namespace CustomValueN {
class IntStrategy : public CustomValueN::FormatStrategy {
   void typed_value() {
//    unless value.blank?
//      value.to_i
//    }
  }

   void validate_type_of_value() {
//    if ( value.is_a? Float) { return :not_an_integer ;}

//    begin
//      Kernel.Integer(value)
//      nil
//    rescue
//      :not_an_integer
//    }
  }
};
}
}
}