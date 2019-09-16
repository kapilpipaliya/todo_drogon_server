#pragma once
#include "../../../queries/users/filters/user_filter.h"
namespace openproj {
namespace Queries {
namespace Users {
namespace Filters {
class LoginFilter : public openproj::Queries::Users::Filters::UserFilter {
   void type() {
//    :string
  }

   void key() {
//    :login
  }
};
}
}
}
}

