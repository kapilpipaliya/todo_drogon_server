#pragma once
#include "../base_query.h"
namespace openproj {
namespace models {
namespace Queries {
namespace Principals {
class PrincipalQuery : public openproj::models::Queries::BaseQuery {
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
}