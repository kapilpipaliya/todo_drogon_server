#pragma once
#include "../../../queries/work_packages/filter/work_package_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class StatusFilter : public openproj::models::Queries::WorkPackages::Filter::WorkPackageFilter {
   void allowed_values() {
//    all_statuses.map { |s| [s.name, s.id.to_s] }
  }

//   void available_operators() {
//    [Queries::Operators::OpenWorkPackages,
//     Queries::Operators::Equals,
//     Queries::Operators::ClosedWorkPackages,
//     Queries::Operators::NotEquals,
//     Queries::Operators::All]
//  }

//   void available?() {
//    Status.exists?
//  }

   void type() {
//    :list
  }

   void key() {
//    :status_id
  }

   void value_objects() {
//    values_ids = values.map(&:to_i)

//    all_statuses.select { |status| values_ids.include?(status.id) }
  }

   void allowed_objects() {
//    all_statuses
  }

//   void ar_object_filter?() {
//    true
//  }

  private:

   void all_statuses() {
//    this->all_statuses ||= Status.all
  }

   void operator_strategy() {
//    super_value = super

//    if ( !super_value) {
//      case operator
//      when "o"
//        Queries::Operators::OpenWorkPackages
//      when "c"
//        Queries::Operators::ClosedWorkPackages
//      when "*"
//        Queries::Operators::All
//      }
//    else
//      super_value
//    }
  }
};
}
}
}
}
}