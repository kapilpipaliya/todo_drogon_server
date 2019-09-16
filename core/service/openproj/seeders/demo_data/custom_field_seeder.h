#pragma once
#include "../seeder.h"
namespace openproj {
namespace seeder {
namespace DemoData {
  class CustomFieldSeeder : public Seeder {
  public:
//    attr_reader :project, :key

//     CustomFieldSeeder(project, key) {
//      this->project = project
//      this->key = key
//    }

     void seed_data() {
//      // Careful: The seeding recreates the seeded project before it runs, so any changes
//      // on the seeded project will be lost.
//      print '    ↳ Creating custom fields...'

//      // create some custom fields and add them to the project
//      Array(project_data_for(key,'custom_fields')).each { |name|
//        cf = WorkPackageCustomField.create!(
//          name: name,
//          regexp: '',
//          is_required: false,
//          min_length: false,
//          default_value: '',
//          max_length: false,
//          editable: true,
//          possible_values: '',
//          visible: true,
//          field_format: 'text'
//        )
//        print '.'

//        project.work_package_custom_fields << cf
//      }

//      puts
    }

     bool applicable() {
//      not WorkPackageCustomField.any?
    }
  };
}
}
}
