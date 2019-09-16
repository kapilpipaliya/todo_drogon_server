#pragma once
#include "../../../queries/filters/strategies/integer.h"
namespace openproj {
namespace Queries::Filters::Strategies {
  class DateTimePast : public openproj::Queries::Filters::Strategies::Integer {
//    this->supported_operators = ['>t-', '<t-', 't-', 't', 'w', '=d', '<>d']
//    this->default_operator = '>t-'

     void validate() {
//      if ( operator == Queries::Operators::OnDateTime ||) {
//         operator == Queries::Operators::BetweenDateTime
//        validate_values_all_datetime
//      else
//        super
//      }
    }

    private:

     void operator_map() {
//      super_value = super.dup
//      super_value['=d'] = Queries::Operators::OnDateTime
//      super_value['<>d'] = Queries::Operators::BetweenDateTime

//      super_value
    }

     void validate_values_all_datetime() {
//      unless values.all? { |value| value.blank? || datetime?(value) }
//        errors.add(:values, I18n.t('activerecord.errors.messages.not_a_datetime'))
//      }
    }

//     void datetime?(str) {
//      if ( ::DateTime.parse(str)) { true ;}
//    rescue ArgumentError
//      false
//    }
  };
}
}
