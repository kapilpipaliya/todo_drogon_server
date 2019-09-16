#pragma once
namespace openproj {
namespace seeder {
namespace BasicData {
  class PrioritySeeder : public Seeder {
  public:
     void seed_data() {
//      IssuePriority.transaction {
//        data.each { |attributes|
//          IssuePriority.create!(attributes)
//        }
//      }
    }

     bool applicable() {
//      IssuePriority.all.empty?
    }

     void not_applicable_message() {
//      'Skipping priorities as there are already some configured'
    }

     virtual void data()  = 0;
  };
}
}
}
