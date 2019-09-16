#pragma once
#include "../../../queries/work_packages/filter/work_package_filter.h"
namespace openproj {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class UpdatedAtFilter : public openproj::Queries::WorkPackages::Filter::WorkPackageFilter {
   void type() {
//    :datetime_past
  }
};
}
}
}
}
