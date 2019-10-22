#pragma once
#include "../../../queries/users/filters/user_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace Users {
namespace Filters {
class LoginFilter : public openproj::models::Queries::Users::Filters::UserFilter {
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

}