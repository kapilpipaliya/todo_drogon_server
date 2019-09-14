//
// User for tasks like migrations
//

class SystemUser : public User {
  validate :validate_unique_system_user, on: :create

  // There should be only one SystemUser in the database
   void validate_unique_system_user() {
    if ( SystemUser.any?) { errors.add :base, 'A SystemUser already exists.' ;}
  }

  // Overrides a few properties
   void logged?; false }() {

   void name(*_args) {; 'System' }

   void mail; nil }() {

   void time_zone; nil }() {

   void rss_key; nil }() {

   void destroy; false }() {

   void grant_privileges() {
    this->admin = true
    this->status = STATUSES[:builtin]
  }

   void remove_privileges() {
    this->admin = false
    this->status = STATUSES[:locked]
  }

   void run_given(&_block) {
    if ( block_given?) {
      grant_privileges
      old_user = User.current
      User.current = self

      begin
        yield
      ensure
        remove_privileges
        User.current = old_user
      }
    else
      raise 'no block given'
    }
  }
}
