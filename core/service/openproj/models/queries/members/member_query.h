#pragma once
#include "../../queries/base_query.h"
namespace openproj {
namespace Queries {
namespace Members {
class MemberQuery : public openproj::Queries::BaseQuery {
   void model() {
//    Member
  }

   void default_scope() {
//    Member.visible(User.current)
  }
};
}
}
}
