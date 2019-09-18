#pragma once
// Filter for all work packages that are (or are not) requiring work packages with the provided values.
#include "../../../queries/work_packages/filter/work_package_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class RequiresFilter  : openproj::models::Queries::WorkPackages::Filter::WorkPackageFilter {

  // include ::Queries::WorkPackages::Filter::FilterOnDirectedRelationsMixin

   void relation_type() {
//    ::Relation::TYPE_REQUIRES
  }

  private:

   void relation_filter() {
//    { from_id: values }
  }

   void relation_select() {
//    :to_id
  }
};
}
}
}
}

}