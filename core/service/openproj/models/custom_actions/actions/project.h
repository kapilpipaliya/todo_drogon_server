class CustomActions::Actions::Project : public CustomActions::Actions::Base {
  // include CustomActions::Actions::Strategies::Associated

  PRIORITY = 10

   void key() {
    :project
  }

   void required?() {
    true
  }

   void priority() {
    PRIORITY
  }

  private:

   void associated() {
    ::Project
      .select(:id, :name)
      .order(Arel.sql('LOWER(name)'))
      .map { |u| [u.id, u.name] }
  }
}
