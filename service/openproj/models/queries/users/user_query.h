#pragma once
#include "../base_query.h"
namespace openproj {
namespace models {
namespace Queries {
namespace Users {
class UserQuery : public openproj::models::Queries::BaseQuery {
   void model() {
//    User
  }

   void default_scope() {
//    User.not_builtin
  }
};
}
}
}


}