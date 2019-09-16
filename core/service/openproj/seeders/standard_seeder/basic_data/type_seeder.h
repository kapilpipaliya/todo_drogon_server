#pragma once
#include "../basic_data/type_seeder.h"
namespace openproj {
namespace seeder {
namespace StandardSeeder {
  namespace BasicData {
    class TypeSeeder : public seeder::BasicData::TypeSeeder {
    public:
       void type_names() {
//        %i[task milestone phase feature epic user_story bug]
      }

       void type_table() {
//        { // position is_default color_id is_in_roadmap is_milestone
//          task:       [1, true, :default_color_blue,        true,  false, :default_type_task],
//          milestone:  [2, true, :default_color_green_light, false, true,  :default_type_milestone],
//          phase:      [3, true, :default_color_blue_dark,   false, false, :default_type_phase],
//          feature:    [4, true, :default_color_blue,        true,  false, :default_type_feature],
//          epic:       [5, true, :default_color_orange,      true,  false, :default_type_epic],
//          user_story: [6, true, :default_color_grey_dark,   true,  false, :default_type_user_story],
//          bug:        [7, true, :default_color_red,         true,  false, :default_type_bug]
//        }
      }
    };
  }
}
}
}
