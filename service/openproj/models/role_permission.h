#ifndef OPENPROJ_MODELS_ROLE_PERMISSION_H
#define OPENPROJ_MODELS_ROLE_PERMISSION_H


#include "activerecord.h"
#include "RolePermissions.h"

namespace openproj {

namespace models {

class RolePermission : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::RolePermissions {
 public:
  void save(){
    auto clientPtr = drogon::app().getDbClient("sce");
    drogon::orm::Mapper<drogon_model::openproject6::RolePermissions> mapper_role_permissions(clientPtr);
    drogon_model::openproject6::RolePermissions* role_permissions = this;
    mapper_role_permissions.insert(*role_permissions);
  }
};

} // namespace openproj::models

} // namespace openproj
#endif
