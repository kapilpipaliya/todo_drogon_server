#pragma once
#include <vector>
#include <memory>
#include "../basic_data/builtin_roles_seeder.h"
#include "../basic_data/color_scheme_seeder.h"
#include "../basic_data/color_seeder.h"
#include "../basic_data/role_seeder.h"
#include "../basic_data/setting_seeder.h"
#include "../basic_data_seeder.h"
#include "./basic_data/activity_seeder.h"
#include "./basic_data/priority_seeder.h"
#include "./basic_data/workflow_seeder.h"
namespace openproj {
namespace seeder {
namespace StandardSeeder {
class BasicDataSeederFinal : public seeder::BasicDataSeeder {
  std::vector<std::shared_ptr<seeder::Seeder>> data;

 public:
  std::shared_ptr<Seeder> builtin_role_seed = std::make_shared<seeder::BasicData::BuiltinRolesSeeder>();
  std::shared_ptr<Seeder> role_seed = std::make_shared<seeder::BasicData::RoleSeeder>();
  std::shared_ptr<Seeder> activity_seed = std::make_shared<seeder::StandardSeeder::BasicData::ActivitySeeder>();
  std::shared_ptr<Seeder> color_seed = std::make_shared<seeder::BasicData::ColorSeeder>();
  std::shared_ptr<Seeder> color_schema_seed = std::make_shared<seeder::BasicData::ColorSchemeSeeder>();
  std::shared_ptr<Seeder> workflow_seed = std::make_shared<seeder::StandardSeeder::BasicData::WorkflowSeeder>();
  std::shared_ptr<Seeder> priority_seed = std::make_shared<seeder::StandardSeeder::BasicData::PrioritySeeder>();
  std::shared_ptr<Seeder> setting_seed = std::make_shared<seeder::BasicData::SettingSeeder>();
  std::vector<std::shared_ptr<seeder::Seeder>>    data_seeder_classes() {
    data.push_back(std::move(builtin_role_seed));
    data.push_back(std::move(role_seed));
    data.push_back(std::move(activity_seed));
    data.push_back(std::move(color_seed));
    data.push_back(std::move(color_schema_seed));
    data.push_back(std::move(workflow_seed));
    data.push_back(std::move(priority_seed));
    data.push_back(std::move(setting_seed));
    return data;
  }
};
}  // namespace StandardSeeder
}  // namespace seeder
}  // namespace openproj
