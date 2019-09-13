class CustomActions::Conditions::Type : public CustomActions::Conditions::Base {
   void key() {
    :type
  }

  private

   void associated() {
    ::Type
      .select(:id, :name)
      .map { |u| [u.id, u.name] }
  }
}
