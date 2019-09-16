#pragma once
#include "base_strategy.h"
namespace openproj {
namespace Queries::Filters::Strategies {
  class Relation : public BaseStrategy {
    // delegate :allowed_values_subset,
    //          to: :filter

//    this->supported_operators = ::Relation::TYPES.keys + %w(parent children)
//    this->default_operator = ::Relation::TYPE_RELATES

     void validate() {
//      unique_values = values.uniq
//      allowed_and_desired_values = allowed_values_subset & unique_values

//      if ( allowed_and_desired_values.sort != unique_values.sort) {
//        errors.add(:values, :inclusion)
//      }
//      if ( too_many_values) {
//        errors.add(:values, "only one value allowed")
//      }
    }

//     void valid_values!() {
//      filter.values &= allowed_values.map(&:last).map(&:to_s)
//    }

    private:

     void too_many_values() {
//      values.reject(&:blank?).length > 1
    }
  };
}
}
