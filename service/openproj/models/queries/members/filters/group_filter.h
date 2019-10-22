#pragma once
#include "../../../queries/members/filters/member_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace Members {
namespace Filters {
class GroupFilter : public openproj::models::Queries::Members::Filters::MemberFilter {
  // include Queries::Filters::Shared::GroupFilter

   void joins() {
//    nil
  }

   void scope() {
//    scope = model.joins(:principal).merge(User.joins(:groups))
//    scope = scope.where(where)
//    scope
  }
};
}
}
}
}
}