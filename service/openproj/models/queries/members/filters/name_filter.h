#pragma once
#include "../../../queries/members/filters/member_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace Members {
namespace Filters {
class NameFilter : public openproj::models::Queries::Members::Filters::MemberFilter {
  // include Queries::Filters::Shared::UserNameFilter

   void joins() {
//    :principal
  }
};
}
}
}
}
}