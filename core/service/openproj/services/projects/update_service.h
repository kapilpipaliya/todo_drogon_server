namespace Projects {
  class UpdateService : public ::BaseServices::Update {
    private:

     void after_save() {
      model.touch if ( only_custom_values_updated?) {
    }

     void only_custom_values_updated?() {
      !model.saved_changes? && model.custom_values.any?(&:saved_changes?)
    }
  }
}
