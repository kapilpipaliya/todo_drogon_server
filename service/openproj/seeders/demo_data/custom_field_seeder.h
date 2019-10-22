#pragma once
#include "../seeder.h"
#include "models/CustomFieldsProjects.h"
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
    //      // Careful: The seeding recreates the seeded project before it runs,
    //      so any changes
    //      // on the seeded project will be lost.
    //      LOG_DEBUG << "    ↳ Creating custom fields..."

    //      // create some custom fields and add them to the project
    //      Array(project_data_for(key,"custom_fields")).each { |name|
    //        cf = WorkPackageCustomField.create!(
    //          name: name,
    //          regexp: "",
    //          is_required: false,
    //          min_length: false,
    //          default_value: "",
    //          max_length: false,
    //          editable: true,
    //          possible_values: "",
    //          visible: true,
    //          field_format: "text"
    //        )
    //        LOG_DEBUG << "."

    //        project.work_package_custom_fields << cf
    //      }

    //      puts

    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::CustomFieldsProjects>
        mapper_custom_fields_projects(clientPtr);
    drogon_model::openproject6::CustomFieldsProjects custom_fields_projects;
    //         custom_fields_projects.set();
    //         custom_fields_projects.setCreatedAt(trantor::Date::now());
    //         custom_fields_projects.setUpdatedAt(trantor::Date::now());
    mapper_custom_fields_projects.insert(custom_fields_projects);
  }

  bool applicable() {
    //      not WorkPackageCustomField.any?
    return true;
  }
};
}  // namespace DemoData
}  // namespace seeder
}  // namespace openproj
