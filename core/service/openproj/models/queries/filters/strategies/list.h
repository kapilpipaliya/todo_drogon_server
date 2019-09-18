#pragma once
#include "base_strategy.h"
namespace openproj {
namespace models {
namespace Queries::Filters::Strategies {
  class List : public BaseStrategy {
    // delegate :allowed_values,
    //          to: :filter

//    this->supported_operators = ['=', '!']
//    this->default_operator = '='

     void validate() {
      // TODO: the -1 is a special value that exists for historical reasons
      // so one can send the operator '=' and the values ['-1']
      // which results in a IS NULL check in the DB.
      // Remove once timelines is removed.
//      if ( non_valid_values?) {
//        errors.add(:values, :inclusion)
//      }
    }

//     void valid_values!() {
//      filter.values &= (allowed_values.map(&:last).map(&:to_s) + ['-1'])
//    }

//     void non_valid_values?() {
//      (values.reject(&:blank?) & (allowed_values.map(&:last).map(&:to_s) + ['-1'])) != values.reject(&:blank?)
//    }
  };
}
}
}