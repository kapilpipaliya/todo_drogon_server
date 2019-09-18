#pragma once
#include "member_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace Members {
namespace Filters {
class RoleFilter : public openproj::models::Queries::Members::Filters::MemberFilter {
   void allowed_values() {
//    this->allowed_values ||= begin
//      Role.pluck(:name, :id).map { |name, id| [name, id] }
//    }
  }

   void type() {
//    :list_optional
  }

   void key() {
//    :role_id
  }

   void joins() {
//    :member_roles
  }

   void where() {
//    operator_strategy.sql_for_field(values, 'member_roles', 'role_id')
  }
};
}
}
}
}
}