#pragma once
#include "format_strategy.h"
namespace openproj {
namespace models {
namespace CustomValueN {
class ARObjectStrategy : public CustomValueN::FormatStrategy {
   void typed_value() {
//    if ( memoized_typed_value) { return memoized_typed_value ;}

//    unless value.blank?
//      RequestStore.fetch(:"#{ar_class.name.underscore}_custom_value_#{value}") {
//        this->memoized_typed_value = ar_object(value)
//      }
//    }
  }

   void formatted_value() {
//    typed_value.to_s
  }

//   void parse_value(val) {
//    if ( val.is_a?(ar_class)) {
//      this->memoized_typed_value = val

//      val.id.to_s
//    } else if ( val.blank?) {
//      super(nil)
//    else
//      super
//    }
//  }

   void validate_type_of_value() {
//    unless custom_field.possible_values(custom_value.customized).include?(value)
//      :inclusion
//    }
  }

  private:

   virtual void ar_class() = 0;

//   virtual void ar_object(_value) = 0;
};
}
}
}