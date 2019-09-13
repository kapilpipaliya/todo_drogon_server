class CustomActions::Conditions::Project : public CustomActions::Conditions::Base {
   void key() {
    :project
  }

  private

   void associated() {
    ::Project
      .select(:id, :name)
      .order(Arel.sql('LOWER(name)'))
      .map { |u| [u.id, u.name] }
  }
}
