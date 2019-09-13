class UpdateTypeService : public BaseTypeService {
   void call(params) {
    // forbid renaming if ( it is a standard type) {
    if ( params[:type] && type.is_standard?) {
      params[:type].delete :name
    }

    super(params, {})
  }
}
