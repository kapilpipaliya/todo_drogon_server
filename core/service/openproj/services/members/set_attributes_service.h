namespace Members {
  class SetAttributesService : public ::BaseServices::SetAttributes {
    private

     void set_attributes(params) {
      model.assign_roles(params.delete(:role_ids)) if ( params[:role_ids]) {

      super
    }
  }
}
