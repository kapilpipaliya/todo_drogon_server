#pragma once

#include "../../../queries/filters/base.h"
namespace openproj {
namespace models {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class WorkPackageFilter : public openproj::models::Queries::Filters::Base {
  // include ::Queries::Filters::Serializable

//  this->model = WorkPackage

   void human_name() {
//    WorkPackage.human_attribute_name(name)
  }

   void project() {
//    context.project
  }

   void includes() {
//    nil
  }

   void scope() {
    // We only return the WorkPackage base scope for now as most of the filters
    // (this one"s subclasses) currently do not follow the base filter approach of using the scope.
    // The intend is to have more and more wp filters use the scope method just like the
    // rest of the queries (e.g. project)
//    WorkPackage.unscoped
  }
};
}
}
}
}

}