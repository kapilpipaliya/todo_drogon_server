#pragma once
#include "../user_password.h"
//
// Password hashing method using bcrypt
namespace openproj {
namespace UserPasswordN {
class Bcrypt : public UserPassword {
//  protected:

  //
  // Determines whether the hashed value of +plain+ matches the stored password hash.
//   void hash_matches?(plain) {
//    BCrypt::Password.new(hashed_password) == plain
//  }

//   void derive_password!(input) {
//    BCrypt::Password.create(input)
//  }
};
}
}
