#pragma once
#include "../../../queries/members/filters/member_filter.h"
namespace openproj {
namespace Queries {
namespace Members {
namespace Filters {
class StatusFilter : public openproj::Queries::Members::Filters::MemberFilter {
  // include Queries::Filters::Shared::UserStatusFilter

   void joins() {
//    :principal
  }
};
}
}
}
}

