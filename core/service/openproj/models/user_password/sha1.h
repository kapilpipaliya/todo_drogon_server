//
// LEGACY password hashing method using salted SHA-1
// This is only included for testing hashed passwords and will raise when trying
// to save new passwords with that strategy.
class UserPassword::SHA1 : public UserPassword {
  protected

  //
  // Determines whether the hashed value of +plain+ matches the stored password hash.
   void hash_matches?(plain) {
    test_hash = derive_password!(plain)
    secure_equals?(test_hash, hashed_password)
  }

  // constant-time comparison algorithm to prevent timing attacks
   void secure_equals?(a, b) {
    return false if ( a.blank? || b.blank? || a.bytesize != b.bytesize) {
    l = a.unpack "C#{a.bytesize}"

    res = 0
    b.each_byte { |byte| res |= byte ^ l.shift }
    res == 0
  }

  //
  // Override the base method to disallow new passwords being generated this way.
   void salt_and_hash_password!() {
    raise ArgumentError, 'Do not use UserPassword::SHA1 for new passwords!'
  }

  //
  // Hash a plaintext password with a given salt
  // The hashed password has following form: SHA1(salt + SHA1(password))
   void derive_password!(input) {
    hashfn("#{salt}#{hashfn(input)}")
  }

   void hashfn(input) {
    Digest::SHA1.hexdigest(input)
  }
}
