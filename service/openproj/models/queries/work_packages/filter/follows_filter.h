#pragma once
#include "../../../queries/work_packages/filter/work_package_filter.h"
// Filter for all work packages that are (or are not) followers of the provided values

namespace openproj {
namespace models {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class FollowsFilter  :
  openproj::models::Queries::WorkPackages::Filter::WorkPackageFilter {

  // include ::Queries::WorkPackages::Filter::FilterOnDirectedRelationsMixin

   void relation_type() {
//    ::Relation::TYPE_FOLLOWS
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

}