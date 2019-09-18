#pragma once
#include "member_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace Members {
namespace Filters {
class BlockedFilter : public openproj::models::Queries::Members::Filters::MemberFilter {
  // include Queries::Filters::Shared::UserBlockedFilter

   void joins() {
//    :principal
  }
};
}
}
}
}

}