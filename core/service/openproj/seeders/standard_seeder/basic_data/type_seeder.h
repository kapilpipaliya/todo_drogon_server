#pragma once
#include "../../basic_data/type_seeder.h"
#include <vector>
#include <map>
namespace openproj {
namespace seeder {
namespace StandardSeeder {
  namespace BasicData {
    class TypeSeeder : public seeder::BasicData::TypeSeeder {
    public:
       std::vector<std::string> type_names() {
//        %i[task milestone phase feature epic user_story bug]
           std::vector<std::string> type_names_{
               "task", "milestone", "phase", "feature", "epic", "user_story", "bug"
           };
           return type_names_;
      }

       std::map<std::string, std::tuple<int, bool, std::string, bool, bool, std::string> > type_table() {
//        { // position is_default color_id is_in_roadmap is_milestone
//          task:       [1, true, :default_color_blue,        true,  false, :default_type_task],
//          milestone:  [2, true, :default_color_green_light, false, true,  :default_type_milestone],
//          phase:      [3, true, :default_color_blue_dark,   false, false, :default_type_phase],
//          feature:    [4, true, :default_color_blue,        true,  false, :default_type_feature],
//          epic:       [5, true, :default_color_orange,      true,  false, :default_type_epic],
//          user_story: [6, true, :default_color_grey_dark,   true,  false, :default_type_user_story],
//          bug:        [7, true, :default_color_red,         true,  false, :default_type_bug]
//        }
        std::map<std::string, std::tuple<int, bool, std::string, bool, bool, std::string> >a{
                  {"task",       {1, true, "Blue",        true,  false, "Task"}},
                  {"milestone",  {2, true, "Green (light)", false, true,  "Milestone"}},
                  {"phase",      {3, true, "Blue (dark)",   false, false, "Phase"}},
                  {"feature",    {4, true, "Blue",        true,  false, "Feature"}},
                  {"epic",       {5, true, "Orange",      true,  false, "Epic"}},
                  {"user_story", {6, true, "Grey (dark)",   true,  false, "User story"}},
                  {"bug",        {7, true, "Red",         true,  false, "Bug"}}
      };
       return a;
    };
  };
}
}
}
}
