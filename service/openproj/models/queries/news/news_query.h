#pragma once
#include "../../queries/base_query.h"
namespace openproj {
namespace models {
namespace Queries {
namespace News {
class NewsQuery : public openproj::models::Queries::BaseQuery {
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
}