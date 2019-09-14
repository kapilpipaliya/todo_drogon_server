namespace openproject {
class CustomActions::Conditions::Status : public CustomActions::Conditions::Base {
   void key() {
    :status
  }

  private:

   void associated() {
    ::Status
      .select(:id, :name)
      .order(:name)
      .map { |u| [u.id, u.name] }
  }
}
