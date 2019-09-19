#pragma once
#include <vector>
#include "composite_seeder.h"
#include "demo_data/attribute_help_text_seeder.h"
#include "demo_data/global_query_seeder.h"
#include "demo_data/group_seeder.h"
#include "demo_data/project_seeder.h"

namespace openproj {
namespace seeder {
class DemoDataSeeder : public CompositeSeeder {
   std::vector<std::shared_ptr<seeder::Seeder>> data;

 public:
   // This 3 is empty
   std::shared_ptr<Seeder> group_seed = std::make_shared<openproj::seeder::DemoData::GroupSeeder>();
   std::shared_ptr<Seeder> attrib_seed = std::make_shared<openproj::seeder::DemoData::AttributeHelpTextSeeder>();
   std::shared_ptr<Seeder> global_seed = std::make_shared<openproj::seeder::DemoData::GlobalQuerySeeder>();

   std::shared_ptr<Seeder> project_seed = std::make_shared<openproj::seeder::DemoData::ProjectSeeder>();

 std::vector<std::shared_ptr<openproj::seeder::Seeder>>  data_seeder_classes() override {
    data.push_back(group_seed);
    data.push_back(attrib_seed);
    data.push_back(global_seed);
    data.push_back(project_seed);
    return data;
  }

  std::string namespace_() { return "DemoData"; }
};
}  // namespace seeder
}  // namespace openproj
