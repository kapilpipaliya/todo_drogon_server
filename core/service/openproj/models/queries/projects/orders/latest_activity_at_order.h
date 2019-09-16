#pragma once
#include "../../../queries/base_order.h"
namespace openproj {
namespace Queries {
namespace Projects {
namespace Orders {
class LatestActivityAtOrder : public openproj::Queries::BaseOrder {
//  this->model = Project

   void key() {
//    :latest_activity_at
  }

  private:

   void order() {
//    with_raise_on_invalid {
//      model.order(Arel.sql("activity.latest_activity_at").send(direction))
//    }
  }
};
}
}
}
}
