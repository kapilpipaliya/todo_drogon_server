#pragma once
#include "../../../queries/work_packages/filter/work_package_filter.h"
// Filter for all work packages that are (or are not) duplicating work packages with the provided values.

namespace openproj {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class DuplicatesFilter  :
  openproj::Queries::WorkPackages::Filter::WorkPackageFilter {

  // include ::Queries::WorkPackages::Filter::FilterOnDirectedRelationsMixin

   void relation_type() {
//    ::Relation::TYPE_DUPLICATES
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

