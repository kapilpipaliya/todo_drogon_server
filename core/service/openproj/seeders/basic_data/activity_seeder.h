#pragma once
#include <drogon/drogon.h>
#include "../seeder.h"
//#include "../../models/time_entry_activity.h"
#include "models/tim

namespace openproj {
namespace seeder {
namespace BasicData {
class ActivitySeeder : public Seeder {
 public:
  struct row {
    std::string name;
    int position;
    bool is_default;
  };
  void seed_data() {
    //      TimeEntryActivity.transaction {
    //        data.each { |attributes|
    //          TimeEntryActivity.create(attributes)
    //        }
    //      }
    auto clientPtr = drogon::app().getDbClient("sce");
    for (auto &it : data2()) {
      drogon::orm::Mapper<drogon_model::openproject4::Roles> mapper(clientPtr);

      drogon_model::openproject4::Roles roles;
      roles.setName(it.name);
      roles.setBuiltin(0);
      roles.setPosition(it.position);
      roles.setType("Role");
      mapper.insert(roles);
      auto id = roles.getId();

      for (auto it_ : it.role_permissions) {
        drogon::orm::Mapper<drogon_model::openproject4::RolePermissions>
            mapper_role_perm(clientPtr);
        drogon_model::openproject4::RolePermissions role_permission;
        role_permission.setPermission(it_);
        role_permission.setRoleId(*id);
        mapper_role_perm.insert(role_permission);
      }
      fflush(stdout);
    }
  }

  bool applicable() {
    //      TimeEntryActivity.all.empty?
  }

  void not_applicable_message() {
    //      'Skipping activities as there are already some configured'
  }

  //     virtual void data()  = 0;
  void data() {}
  virtual std::vector<row> data2() = 0;
};
}  // namespace BasicData
}  // namespace seeder
}  // namespace openproj
