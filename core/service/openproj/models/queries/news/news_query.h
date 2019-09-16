#pragma once
#include "../../queries/base_query.h"
namespace openproj {
namespace Queries {
namespace News {
class NewsQuery : public openproj::Queries::BaseQuery {
   void model() {
//    News
  }

   void default_scope() {
//    News.visible(User.current)
  }
};
}
}
}
