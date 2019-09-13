class CustomActions::Actions::Inexistent : public CustomActions::Actions::Base {
   void key() {
    :inexistent
  }

   void validate(errors) {
    errors.add :actions, :does_not_exist
  }
}
