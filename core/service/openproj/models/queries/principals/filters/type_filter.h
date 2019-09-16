#pragma once
#include "../../../queries/principals/filters/principal_filter.h"
namespace openproj {
namespace Queries {
namespace Principals {
namespace Filters {
class TypeFilter : public openproj::Queries::Principals::Filters::PrincipalFilter {
   void allowed_values() {
//    [[Group.to_s, Group.to_s],
//     [User.to_s, User.to_s]]
  }

   void type() {
//    :list
  }

   void key() {
//    :type
  }

   void scope() {
//    if ( operator == '=') {
//      Principal.where(type: values)
//    else
//      Principal.where.not(type: values)
//    }
  }
};
}
}
}
}

