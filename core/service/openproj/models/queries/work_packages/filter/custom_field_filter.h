#pragma once
#include "../../../queries/work_packages/filter/work_package_filter.h"
namespace openproj {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class CustomFieldFilter  :
  openproj::Queries::WorkPackages::Filter::WorkPackageFilter {

  // include Queries::Filters::Shared::CustomFieldFilter
//  this->custom_field_context = ::Queries::WorkPackages::Filter::CustomFieldContext
};
}
}
}
}

