#pragma once
#include <vector>

#include "../../basic_data/activity_seeder.h"
namespace openproj {
namespace seeder {
namespace StandardSeeder {
  namespace BasicData {
    class ActivitySeeder : public seeder::BasicData::ActivitySeeder {
      std::vector<row> data_;

    public:
       std::vector<row> data2() {
//        [
//          { name: I18n.t(:default_activity_management),    position: 1, is_default: true  },
//          { name: I18n.t(:default_activity_specification), position: 2, is_default: false },
//          { name: I18n.t(:default_activity_development),   position: 3, is_default: false },
//          { name: I18n.t(:default_activity_testing),       position: 4, is_default: false },
//          { name: I18n.t(:default_activity_support),       position: 5, is_default: false },
//          { name: I18n.t(:default_activity_other),         position: 6, is_default: false }
//        ]
         data_.insert(data_.end(), {
           {"Management", 1, true},
           {"Specification", 2, true},
           {"Development", 3, true},
           {"Testing", 4, true},
           {"Support", 5, true},
           {"Other", 6, true},
         });
         return data_;
      }

    };
  }
}
}
}
