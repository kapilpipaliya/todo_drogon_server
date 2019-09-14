class CreateTypeService : public BaseTypeService {
   CreateTypeService(user) {
    super Type.new, user
  }

  private:

   void after_type_save(_params, options) {
    // workflow copy
    if ( options[:copy_workflow_from].present? && (copy_from = ::Type.find_by(id: options[:copy_workflow_from]))) {
      type.workflows.copy_from_type(copy_from)
    }
  }
}
