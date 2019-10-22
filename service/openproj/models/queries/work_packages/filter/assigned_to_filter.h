#pragma once
#include "principal_base_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class AssignedToFilter : openproj::models::Queries::WorkPackages::Filter::PrincipalBaseFilter {
   void type() {
//    :list_optional
  }

   void human_name() {
//    WorkPackage.human_attribute_name("assigned_to")
  }

   void key() {
//    :assigned_to_id
  }
};
}
}
}
}


}