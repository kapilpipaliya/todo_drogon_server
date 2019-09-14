namespace openproject {
class CustomActions::Actions::Status : public CustomActions::Actions::Base {
  // include CustomActions::Actions::Strategies::Associated

   void key() {
    :status
  }

   void required?() {
    true
  }

  private:

   void associated() {
    Status
      .select(:id, :name)
      .order(:name)
      .map { |u| [u.id, u.name] }
  }
}
