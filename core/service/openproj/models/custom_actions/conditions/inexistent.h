namespace openproj {
class CustomActions::Conditions::Inexistent : public CustomActions::Conditions::Base {
   void key() {
    :inexistent
  }

   void validate(errors) {
    errors.add :conditions, :does_not_exist
  }
}
