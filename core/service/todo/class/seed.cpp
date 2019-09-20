#include "seed.h"

#include "./auth.h"

#include <utility>
#include "../../../sql/dba.h"
#include "./session.h"
#include "fmt/format.h"
#include "wscontroller/wsfns.h"
#include "core/service/openproj/seeders/basic_data/builtin_roles_seeder.h"
#include "core/service/openproj/seeders/basic_data/role_seeder.h"
#include "core/service/openproj/seeders/root_seeder.h"
#include "core/service/openproj/seeders/standard_seeder/basic_data/workflow_seeder.h"
#include "core/service/openproj/seeders/standard_seeder/basic_data/type_seeder.h"

namespace todo {
namespace service {
Seed::Seed(std::shared_ptr<websocket::todo::TodoContext> context_)
    : context(std::move(context_)) {
  setupTable();
}

void Seed::setupTable() {}

nlohmann::json Seed::handleEvent(nlohmann::json event, unsigned long next,
                                 nlohmann::json args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "seed1") {
    openproj::seeder::BasicData::BuiltinRolesSeeder a;
    a.seed();
    return {websocket::WsFns::successJsonObject(event, true, "Done")};
  } else if (event_cmp == "seed2") {
    openproj::seeder::BasicData::RoleSeeder a;
    a.seed();
    return {websocket::WsFns::successJsonObject(event, true, "Done")};
  } else if (event_cmp == "seed3") {
      openproj::seeder::BasicData::SettingSeeder a;
      a.seed();
      return {websocket::WsFns::successJsonObject(event, true, "Done")};
  } else if (event_cmp == "seed4") {
      openproj::seeder::StandardSeeder::BasicData::WorkflowSeeder a;
      a.seed();
      return {websocket::WsFns::successJsonObject(event, true, "Done")};
  } else if (event_cmp == "seed5") {
      openproj::seeder::StandardSeeder::BasicData::TypeSeeder a;
      a.seed();
      return {websocket::WsFns::successJsonObject(event, true, "Done")};
  } else if (event_cmp == "seedall") {
      openproj::seeder::RootSeeder a;
      a.seed();
      return {websocket::WsFns::successJsonObject(event, true, "Done")};
  } else {
    return nullptr;
  }
}

}  // namespace service
}  // namespace todo
