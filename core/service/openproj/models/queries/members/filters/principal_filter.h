#pragma once
#include "../../../queries/members/filters/member_filter.h"
namespace openproj {
namespace Queries {
namespace Members {
namespace Filters {
class PrincipalFilter : public openproj::Queries::Members::Filters::MemberFilter {
  // include Queries::Filters::Shared::MeValueFilter

   void allowed_values() {
//    this->allowed_values ||= begin
//      values = Principal
//               .active_or_registered
//               .in_visible_project
//               .map { |s| [s.name, s.id.to_s] }
//               .sort

//      me_allowed_value + values
//    }
  }

//   void available?() {
//    allowed_values.any?
//  }

//   void ar_object_filter?() {
//    true
//  }

//   void principal_resource?() {
//    true
//  }

   void where() {
//    operator_strategy.sql_for_field(values_replaced, this->class.model.table_name, :user_id)
  }

   void type() {
//    :list_optional
  }

   void key() {
//    :principal_id
  }
};
}
}
}
}
