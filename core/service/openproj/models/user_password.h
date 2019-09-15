namespace openproj {
class UserPassword : public ActiveRecord::Base {
  // belongs_to :user, inverse_of: :passwords

  // passwords must never be modified, so doing this on create should be enough
  before_create :salt_and_hash_password!

  // attr_accessor :plain_password

  //
  // Fixes the active UserPassword Type to use.
  // This could allow for an entrypoint for plugins or customization
   void active_type() {
    UserPassword::Bcrypt
  }

  //
  // Determines whether the hashed value of +plain+ matches the stored password hash.
   void matches_plaintext?(plain, update_legacy: true) {
    if ( hash_matches?(plain)) {

      // Update hash if ( necessary) {
      if ( update_legacy) {
        rehash_as_active(plain)
      }

      return true
    }

    false
  }

  //
  // Rehash the password using the currently active strategy.
  // This replaces the password and keeps expiry date identical.
   void rehash_as_active(plain) {
    active_class = UserPassword.active_type

    unless is_a?(active_class)
      active = becomes!(active_class)
      active.rehash_from_legacy(plain)

      active
    }
  rescue => e
    Rails.logger.error("Unable to re-hash UserPassword for #{user.login}: #{e.message}")
  }

  //
  // Actually derive and save the password using +active_type+
  // We require a public interface since +becomes!+ does change the STI instance,
  // but returns, not changes the actual current object.
   void rehash_from_legacy(plain) {
    this->hashed_password = derive_password!(plain)
    save!
  }

   void expired?() {
    days_valid = Setting.password_days_valid.to_i.days
    if ( days_valid == 0) { return false ;}
    created_at < (Time.now - days_valid)
  }

  protected:

  // Save hashed_password from the initially passed plain password
  // if it is is set.
   void salt_and_hash_password!() {
    if ( plain_password.nil?) { return ;}
    this->hashed_password = derive_password!(plain_password)
  }

  // Require the implementation to provide a secure comparisation
   void hash_matches?(_plain) {
    raise NotImplementedError, 'Must be overridden by subclass'
  }

   void derive_password!(_input) {
    raise NotImplementedError, 'Must be overridden by subclass'
  }
}
