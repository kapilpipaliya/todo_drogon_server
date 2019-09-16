#pragma once
#include "principal_base_filter.h"
namespace openproj {
namespace Queries {
namespace WorkPackages {
namespace Filter {
class AuthorFilter  :
    openproj::Queries::WorkPackages::Filter::PrincipalBaseFilter {
   void allowed_values() {
//    this->author_values ||= begin
//      me_allowed_value + principal_loader.user_values
//    }
  }

   void type() {
//    :list
  }

   void key() {
//    :author_id
  }
};
}
}
}
}

