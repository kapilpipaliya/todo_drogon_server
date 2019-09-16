#pragma once
#include "../../../queries/members/filters/member_filter.h"
namespace openproj {
namespace Queries {
namespace Members {
namespace Filters {
class NameFilter : public openproj::Queries::Members::Filters::MemberFilter {
  // include Queries::Filters::Shared::UserNameFilter

   void joins() {
//    :principal
  }
};
}
}
}
}
