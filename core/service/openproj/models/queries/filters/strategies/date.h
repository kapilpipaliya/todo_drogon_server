#pragma once
#include "../../../queries/filters/strategies/integer.h"
namespace openproj {
namespace Queries::Filters::Strategies {
  class Date : public openproj::Queries::Filters::Strategies::Integer {
//    this->supported_operators = ['<t+', '>t+', 't+', 't', 'w', '>t-', '<t-', 't-', '=d', '<>d']
//    this->default_operator = 't'

//     void validate() {
//      if ( operator == Queries::Operators::OnDate ||) {
//         operator == Queries::Operators::BetweenDate
//        validate_values_all_date
//      else
//        super
//      }
//    }

    private:

//     void validate_values_all_date() {
//      unless values.all? { |value| value.blank? || date?(value) }
//        errors.add(:values, I18n.t('activerecord.errors.messages.not_a_date'))
//      }
//    }

//     void date?(str) {
//      if ( ::Date.parse(str)) { true ;}
//    rescue ArgumentError
//      false
//    }
  };
}
}
