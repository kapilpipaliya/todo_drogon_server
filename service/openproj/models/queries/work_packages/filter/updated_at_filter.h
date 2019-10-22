#pragma once
#include "../../../queries/work_packages/filter/work_package_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class UpdatedAtFilter : public openproj::models::Queries::WorkPackages::Filter::WorkPackageFilter {
   void type() {
//    :datetime_past
  }
};
}
}
}
}
}