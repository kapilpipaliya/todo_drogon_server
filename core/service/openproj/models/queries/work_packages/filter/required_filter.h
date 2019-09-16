#pragma once
// Filter for all work packages that are (or are not) required by work packages with the provided values.
#include "../../../queries/work_packages/filter/work_package_filter.h"
namespace openproj {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class RequiredFilter  : openproj::Queries::WorkPackages::Filter::WorkPackageFilter {

  // include ::Queries::WorkPackages::Filter::FilterOnDirectedRelationsMixin

   void relation_type() {
//    ::Relation::TYPE_REQUIRED
  }

  private:

   void relation_filter() {
//    { to_id: values }
  }

   void relation_select() {
//    :from_id
  }
};
}
}
}
}

