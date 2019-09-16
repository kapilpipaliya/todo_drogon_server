#pragma once
#include "../base_query.h"
namespace openproj {
namespace Queries {
namespace Principals {
class PrincipalQuery : public openproj::Queries::BaseQuery {
   void model() {
//    Principal
  }

   void default_scope() {
//    Principal.not_builtin
  }
};
}
}
}
