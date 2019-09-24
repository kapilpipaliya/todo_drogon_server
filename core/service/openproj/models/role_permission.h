#ifndef OPENPROJ_MODELS_ROLE_PERMISSION_H
#define OPENPROJ_MODELS_ROLE_PERMISSION_H


#include "activerecord.h"
#include "RolePermissions.h"

namespace openproj {

namespace models {

class RolePermission : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::RolePermissions {
};

} // namespace openproj::models

} // namespace openproj
#endif
