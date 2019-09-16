#pragma once
namespace openproj {
namespace seeder {
namespace BasicData {
  class StatusSeeder : public Seeder {
  public:
     void seed_data() {
//      Status.transaction {
//        data.each { |attributes|
//          Status.create!(attributes)
//        }
//      }
    }

     bool applicable() {
//      Status.all.any?
    }

     void not_applicable_message() {
//      'Skipping statuses - already exists/configured'
    }

     void data() {
//      raise NotImplementedError
    }
  };
}
}
}
