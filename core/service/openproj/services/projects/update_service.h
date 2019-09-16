#pragma once
#include "../../services/base_services/update.h"
namespace openproj {
namespace service {
namespace Projects {
  class UpdateService : public BaseServices::Update {
  public:
    private:

     void after_save() {
//      if ( only_custom_values_updated?) { model.touch ;}
    }

     bool only_custom_values_updated() {
//      !model.saved_changes? && model.custom_values.any?(&:saved_changes?)
    }
  };
}
}
}
