#pragma once
#include "../../../queries/work_packages/filter/principal_base_filter.h"
namespace openproj {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class ResponsibleFilter  : openproj::Queries::WorkPackages::Filter::PrincipalBaseFilter {

   void type() {
//    :list_optional
  }

   void key() {
//    :responsible_id
  }
};
}
}
}
}
