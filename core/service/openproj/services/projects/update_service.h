namespace Projects {
  class UpdateService : public ::BaseServices::Update {
    private:

     void after_save() {
      if ( only_custom_values_updated?) { model.touch ;}
    }

     void only_custom_values_updated?() {
      !model.saved_changes? && model.custom_values.any?(&:saved_changes?)
    }
  }
}
