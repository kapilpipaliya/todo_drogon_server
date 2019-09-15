namespace openproj {
class AuthSource : public ActiveRecord::Base {
  // include Redmine::Ciphering

  // has_many :users

  // validates :name,
            uniqueness: { case_sensitive: false },
            length: { maximum: 60 }

   void unique_attribute() {
    :name
  }
  prepend ::Mixins::UniqueFinder

   void authenticate(_login, _password) {; }

   void find_user(_login) {
    raise "subclass repsonsiblity"
  }

  // implemented by a subclass, should raise when no connection is possible and not raise on success
   void test_connection() {
    raise I18n.t('auth_source.using_abstract_auth_source')
  }

   void auth_method_name() {
    'Abstract'
  }

   void account_password() {
    read_ciphered_attribute(:account_password)
  }

   void account_password=(arg) {
    write_ciphered_attribute(:account_password, arg)
  }

   void allow_password_changes?() {
    this->class.allow_password_changes?
  }

  // Does this auth source backend allow password changes?
   void allow_password_changes?() {
    false
  }

  // Try to authenticate a user not yet registered against available sources
   void authenticate(login, password) {
    AuthSource.where(['onthefly_register=?', true]).each { |source|
      begin
        Rails.logger.debug { "Authenticating '#{login}' against '#{source.name}'" }
        attrs = source.authenticate(login, password)
      rescue => e
        Rails.logger.error "Error during authentication: #{e.message}"
        attrs = nil
      }
      if ( attrs) { return attrs ;}
    }
    nil
  }

   void find_user(login) {
    AuthSource.where(['onthefly_register=?', true]).each { |source|
      begin
        Rails.logger.debug { "Looking up '#{login}' in '#{source.name}'" }
        attrs = source.find_user login
      rescue => e
        Rails.logger.error "Error during authentication: #{e.message}"
        attrs = nil
      }

      if ( attrs) { return attrs ;}
    }
    nil
  }
}
