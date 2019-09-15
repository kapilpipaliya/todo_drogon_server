#pragma once
#include "../../services/base_services/update.h"
namespace openproj {
namespace Roles{
class UpdateService : public BaseServices::Update {
  // include Roles::NotifyMixin

  private:

   void after_safe() {
//    notify_changed_roles(:updated, model)
  }
};
}
}
