#pragma once
#include "../seeder.h"
namespace openproj {
namespace seeder {
namespace BasicData {
  class ActivitySeeder : public Seeder {
  public:
     void seed_data() {
//      TimeEntryActivity.transaction {
//        data.each { |attributes|
//          TimeEntryActivity.create(attributes)
//        }
//      }
    }

     bool applicable() {
//      TimeEntryActivity.all.empty?
    }

     void not_applicable_message() {
//      'Skipping activities as there are already some configured'
    }

     virtual void data()  = 0;
  };
}
}
}
