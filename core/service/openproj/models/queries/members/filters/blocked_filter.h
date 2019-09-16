#pragma once
#include "member_filter.h"
namespace openproj {
namespace Queries {
namespace Members {
namespace Filters {
class BlockedFilter : public openproj::Queries::Members::Filters::MemberFilter {
  // include Queries::Filters::Shared::UserBlockedFilter

   void joins() {
//    :principal
  }
};
}
}
}
}

