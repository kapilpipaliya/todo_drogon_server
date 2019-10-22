#pragma once
#include "../../../queries/principals/filters/principal_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace Principals {
namespace Filters {
class StatusFilter : public openproj::models::Queries::Principals::Filters::PrincipalFilter {
   void allowed_values() {
//    ::Principal::STATUSES.map { |key, value|
//      [key, value]
//    }
  }

   void type() {
//    :list
  }

   void key() {
//    :status
  }
};
}
}
}
}

}