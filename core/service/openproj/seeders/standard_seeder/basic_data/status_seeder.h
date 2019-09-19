#pragma once
#include "../../basic_data/status_seeder.h"
#include <vector>
#include <string>

#include <map>
namespace openproj {
namespace seeder {
namespace StandardSeeder {
  namespace BasicData {
    class StatusSeeder : public seeder::BasicData::StatusSeeder {
    public:
       std::vector<row> data() {
//        color_names = [
//          "teal-1", // new
//          "indigo-1", // in specification
//          "teal-3", // specified
//          "red-6", // confirmed
//          "yellow-2", // tbs
//          "lime-2", // scheduled
//          "cyan-3", // in progress
//          "cyan-3", // in development
//          "teal-6", // developed
//          "teal-7", // in testing
//          "teal-9", // tested
//          "red-9", // test_failed
//          "gray-3", // closed
//          "orange-3", // on hold
//          "red-3", // rejected
//        ]

//        // When selecting for an array of values, implicit order is applied
//        // so we need to restore values by their name.
//        colors_by_name = Color.where(name: color_names).index_by(&:name)
//        colors = color_names.collect { |name| colors_by_name[name].id }

//        [
//          { name: I18n.t(:default_status_new),              color_id: colors[0], is_closed: false, is_default: true,  position: 1  },
//          { name: I18n.t(:default_status_in_specification), color_id: colors[1], is_closed: false, is_default: false, position: 2  },
//          { name: I18n.t(:default_status_specified),        color_id: colors[2], is_closed: false, is_default: false, position: 3  },
//          { name: I18n.t(:default_status_confirmed),        color_id: colors[3], is_closed: false, is_default: false, position: 4  },
//          { name: I18n.t(:default_status_to_be_scheduled),  color_id: colors[4], is_closed: false, is_default: false, position: 5  },
//          { name: I18n.t(:default_status_scheduled),        color_id: colors[5], is_closed: false, is_default: false, position: 6  },
//          { name: I18n.t(:default_status_in_progress),      color_id: colors[6], is_closed: false, is_default: false, position: 7  },
//          { name: I18n.t(:default_status_developed),        color_id: colors[8], is_closed: false, is_default: false, position: 9  },
//          { name: I18n.t(:default_status_in_testing),       color_id: colors[9], is_closed: false, is_default: false, position: 10 },
//          { name: I18n.t(:default_status_tested),           color_id: colors[10], is_closed: false, is_default: false, position: 11 },
//          { name: I18n.t(:default_status_test_failed),      color_id: colors[11], is_closed: false, is_default: false, position: 12 },
//          { name: I18n.t(:default_status_closed),           color_id: colors[12], is_closed: true,  is_default: false, position: 13 },
//          { name: I18n.t(:default_status_on_hold),          color_id: colors[13], is_closed: false, is_default: false, position: 14 },
//          { name: I18n.t(:default_status_rejected),         color_id: colors[14], is_closed: true,  is_default: false, position: 15 }
//        ]
           std::vector<std::string> color_names{
                 "teal-1", // new
                 "indigo-1", // in specification
                 "teal-3", // specified
                 "red-6", // confirmed
                 "yellow-2", // tbs
                 "lime-2", // scheduled
                 "cyan-3", // in progress
                 "cyan-3", // in development
                 "teal-6", // developed
                 "teal-7", // in testing
                 "teal-9", // tested
                 "red-9", // test_failed
                 "gray-3", // closed
                 "orange-3", // on hold
                 "red-3" // rejected
           };
           //todo: doing batch search is good too here for color_id;
           data_.insert(data_.end(), {

                         { "New",              color_names[0], false, true,  1  },
                         { "default_status_in_specification", color_names[1], false, false, 2  },
                         { "In specification",        color_names[2], false, false, 3  },
                         { "Confirmed",        color_names[3], false, false, 4  },
                         { "To be scheduled",  color_names[4], false, false, 5  },
                         { "Scheduled",        color_names[5], false, false, 6  },
                         { "In progress",      color_names[6], false, false, 7  },
                         { "Developed",        color_names[8], false, false, 9  },
                         { "In testing",       color_names[9], false, false, 10 },
                         { "Tested",           color_names[10], false, false, 11 },
                         { "Test failed",      color_names[11], false, false, 12 },
                         { "Closed",           color_names[12], true,  false, 13 },
                         { "On hold",          color_names[13], false, false, 14 },
                         { "Rejected",         color_names[14], true,  false, 15 }
               });
           return data_;
           }
    };
  }
}
}
}
