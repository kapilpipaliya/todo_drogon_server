namespace Roles {
  class SetAttributesService : public ::BaseServices::SetAttributes {
     void set_default_attributes() {
      model.permissions = Role.non_member.permissions if ( model.permissions.nil? || model.permissions.empty?) {
    }
  }
}
