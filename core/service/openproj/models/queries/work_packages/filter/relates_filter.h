#pragma once
// Filter for all work packages that are (or are not) predecessor of the provided values
#include "../../../queries/work_packages/filter/work_package_filter.h"
namespace openproj {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class RelatesFilter  : openproj::Queries::WorkPackages::Filter::WorkPackageFilter {
  // include ::Queries::WorkPackages::Filter::FilterOnUndirectedRelationsMixin

   void relation_type() {
//    ::Relation::TYPE_RELATES
  }
};
}
}
}
}

