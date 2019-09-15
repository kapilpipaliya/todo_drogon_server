namespace openproj {
class CustomActions::Actions::Priority : public CustomActions::Actions::Base {
  // include CustomActions::Actions::Strategies::Associated

   void associated() {
    IssuePriority
      .select(:id, :name)
      .order(:name)
      .map { |p| [p.id, p.name] }
  }

   void required?() {
    true
  }

   void key() {
    :priority
  }
}
