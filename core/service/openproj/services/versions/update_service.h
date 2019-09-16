#pragma once
#include "../../services/base_services/update.h"
namespace openproj {
namespace service {
namespace Versions {
  class UpdateService : public BaseServices::Update {
    private:

//     void after_save() {
//      if ( only_custom_values_updated?) { model.touch ;}
//      if ( model.saved_change_to_sharing?) { update_wps_from_sharing_change ;}
//    }

//    if ( a version's sharing changes.) { // Update the issue's fixed versions. Used ;}
//     void update_wps_from_sharing_change() {
//      if ( no_valid_version_before_or_now? ||) {
//         sharing_now_less_broad?
//        WorkPackage.update_versions_from_sharing_change model
//      }
//    }

//     void only_custom_values_updated?() {
//      !model.saved_changes? && model.custom_values.any?(&:saved_changes?)
//    }

//     void no_valid_version_before_or_now?() {
//      version_sharings.index(model.sharing_before_last_save).nil? ||
//        version_sharings.index(model.sharing).nil?
//    }

//     void sharing_now_less_broad?() {
//      version_sharings.index(model.sharing_before_last_save) > version_sharings.index(model.sharing)
//    }

//     void version_sharings() {
//      Version::VERSION_SHARINGS
//    }
  };
}
}
}
