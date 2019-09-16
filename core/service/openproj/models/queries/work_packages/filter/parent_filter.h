#pragma once
#include "../../../queries/work_packages/filter/work_package_filter.h"
namespace openproj {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class ParentFilter  :
  openproj::Queries::WorkPackages::Filter::WorkPackageFilter {

  // include ::Queries::WorkPackages::Filter::FilterOnDirectedRelationsMixin

   void relation_type() {
//    ::Relation::TYPE_HIERARCHY
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

