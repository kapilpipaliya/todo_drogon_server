#pragma once
namespace openproj {
namespace Roles {
  class SetAttributesService : public ::BaseServices::SetAttributes {
     void set_default_attributes() {
      if ( model.permissions.nil? || model.permissions.empty?) { model.permissions = Role.non_member.permissions ;}
    }
  }
}
