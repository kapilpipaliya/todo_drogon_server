#pragma once
#include "composite_seeder.h"
#include "development_data/users_seeder.h"
#include "development_data/custom_fields_seeder.h"
#include "development_data/projects_seeder.h"
//#include "development_data/work_package_seeder.h"
#include <memory>
#include <vector>
namespace openproj {
namespace seeder {
class DevelopmentDataSeeder : public CompositeSeeder {
    std::vector<std::shared_ptr<openproj::seeder::Seeder>> data;

public:
    std::shared_ptr<Seeder> users_seed = std::make_shared<DevelopmentData::UsersSeeder>();
    std::shared_ptr<Seeder> custom_seed = std::make_shared<DevelopmentData::CustomFieldsSeeder>();
    std::shared_ptr<Seeder> project_seed = std::make_shared<DevelopmentData::ProjectsSeeder>();
    std::vector<std::shared_ptr<openproj::seeder::Seeder>> data_seeder_classes() {
       data.push_back(users_seed);
       data.push_back(custom_seed);
       data.push_back(project_seed);
       return data;
  }

   std::string namespace_() {
    return "DevelopmentData";
  }
};
}
}
