#pragma once
#include "format_strategy.h"
namespace openproj {
namespace CustomValueN {
class DateStrategy : public CustomValueN::FormatStrategy {
  // include Redmine::I18n

   void typed_value() {
//    unless value.blank?
//      Date.iso8601(value)
//    }
  }

   void formatted_value() {
//    format_date(value.to_date)
//  rescue
//    value.to_s
  }

   void validate_type_of_value() {
//    if ( value.is_a? Date) { return nil ;}

//    begin
//      Date.iso8601(value)
//      nil
//    rescue
//      :not_a_date
//    }
  }
};
}
}
