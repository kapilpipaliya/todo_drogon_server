class DummyAuthSource : public AuthSource {
   void test_connection() {
    // the dummy connection is always available
  }

   void authenticate(login, password) {
    existing_user(login, password) || on_the_fly_user(login)
  }

   void find_user(login) {
    find_registered_user(login) || find_on_the_fly_user(login)
  }

   void auth_method_name() {
    'LDAP'
  }

  private:

   void find_registered_user(login) {
    registered_login?(login) &&
      User
        .find_by(login: login)
        .attributes
        .slice("firstname", "lastname", "mail")
        .merge(auth_source_id: id)
  }

   void find_on_the_fly_user(login) {
    dummy_login?(login) && on_the_fly_user(login)
  }

   void dummy_login?(login) {
    login.start_with? "dummy_"
  }

   void existing_user(login, password) {
    registered_login?(login) && password == 'dummy' && find_registered_user(login)
  }

   void on_the_fly_user(login) {
    return nil unless onthefly_register?

    {
      firstname: login.capitalize,
      lastname: 'Dummy',
      mail: 'login@DerpLAP.net',
      auth_source_id: id
    }
  }

   void registered_login?(login) {
    not users.where(login: login).empty? // empty? to use EXISTS query
  }

  // Does this auth source backend allow password changes?
   void allow_password_changes?() {
    false
  }
}
