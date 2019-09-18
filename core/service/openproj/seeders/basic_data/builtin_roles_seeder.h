#pragma once
#include "../seeder.h"
#include "../../models/role.h"
#include <vector>
#include "models/Roles.h"
#include <drogon/drogon.h>
namespace openproj {
namespace seeder {
namespace BasicData {
  class BuiltinRolesSeeder : public Seeder {
    struct row {
      std::string name;
      int position;
      openproj::models::Role::AAA role;
    };
    std::vector<row> data_;

  public:
     void seed_data() {
//      data.each { |attributes|
//        unless Role.find_by(builtin: attributes[:builtin]).nil?
//          puts "   *** Skipping built in role #{attributes[:name]} - already exists"
//          next
//        }

//        Role.create(attributes)
//      }
         for (auto &it : data()) {
             auto clientPtr = drogon::app().getDbClient("sce");
            drogon::orm::Mapper<drogon_model::openproject4::Roles> mapper(clientPtr);
            drogon_model::openproject4::Roles roles;
            roles.setName(it.name);
            roles.setPosition(it.position);
            roles.setBuiltin(it.role);
            mapper.insert(roles);
         }
    }


     std::vector<row> data() {
//      [
//        { name: I18n.t(:default_role_non_member), position: 0, builtin: Role::BUILTIN_NON_MEMBER },
//        { name: I18n.t(:default_role_anonymous),  position: 1, builtin: Role::BUILTIN_ANONYMOUS  }
//      ]
         //config/locales/en.yml
         data_.push_back({std::string("Non member"), 0, openproj::models::Role::BUILTIN_NON_MEMBER});
         data_.push_back({std::string("Anonymous"), 1, openproj::models::Role::BUILTIN_ANONYMOUS});
         return data_;
    }
  };
}
}
}
