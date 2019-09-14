namespace Members {
  class SetAttributesService : public ::BaseServices::SetAttributes {
    private:

     void set_attributes(params) {
      if ( params[:role_ids]) { model.assign_roles(params.delete(:role_ids)) ;}

      super
    }
  }
}