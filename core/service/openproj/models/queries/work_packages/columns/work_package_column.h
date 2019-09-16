#pragma once
#include "../../../queries/columns/base.h"
namespace openproj {
namespace Queries {
namespace WorkPackages {
namespace Columns {
class WorkPackageColumn : public openproj::Queries::Columns::Base {
  // attr_accessor :highlightable
//  alias_method :highlightable?, :highlightable

//   WorkPackageColumn(name, options = {}) {
//    super(name, options)
//    this->highlightable = !!options.fetch(:highlightable, false)
//  }

   void caption() {
//    WorkPackage.human_attribute_name(name)
  }

//   void sum_of(work_packages) {
//    if ( work_packages.is_a?(Array)) {
//      // TODO: Sums::grouped_sums might call through here without an AR::Relation
//      // Ensure that this also calls using a Relation and drop this (slow!) implementation
//      work_packages.map { |wp| value(wp) }.compact.reduce(:+)
//    else
//      work_packages.sum(name)
//    }
//  }
};
}
}
}
}
