#pragma once
#include "work_package_filter.h"
namespace openproj {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class PrincipalBaseFilter  : openproj::Queries::WorkPackages::Filter::WorkPackageFilter {
  // include MeValueFilterMixin

   void allowed_values() {
//    this->allowed_values ||= begin
//      values = principal_loader.user_values

//      if ( Setting.work_package_group_assignment?) {
//        values += principal_loader.group_values
//      }

//      me_allowed_value + values.sort
//    }
  }

//   void available?() {
//    User.current.logged? || allowed_values.any?
//  }

//   void ar_object_filter?() {
//    true
//  }

//   void principal_resource?() {
//    true
//  }

   void where() {
//    operator_strategy.sql_for_field(values_replaced, this->class.model.table_name, this->class.key)
  }

  private:

   void principal_loader() {
//    this->principal_loader ||= ::Queries::WorkPackages::Filter::PrincipalLoader.new(project)
  }
};
}
}
}
}
