#pragma once
//require_dependency 'token/base'
#include "base.h"
namespace openproj {
namespace Token {
  class HashedToken : public Base {
    // Allow access to the plain value during initial access / creation of the token
//    attr_reader :plain_value

//    class << self {
//       void create_and_return_value(user) {
//        create(user: user).plain_value
//      }

//      //
//      // Find a token from the token value
//       void find_by_plaintext_value(input) {
//        find_by(value: hash_function(input))
//      }
//    }

    //
    // Validate the user input on the token
    // 1. The token is still valid
    // 2. The plain text matches the hash
//     void valid_plaintext?(input) {
//      hashed_input = hash_function(input)
//      ActiveSupport::SecurityUtils.secure_compare hashed_input, value
//    }

//     void hash_function(input) {
//      // Use a fixed salt for hashing token values.
//      // We still want to be able to index the hash value for fast lookups,
//      // so we need to determine the hash without knowing the associated user (and thus its salt) first.
//      Digest::SHA256.hexdigest(input + Rails.application.secrets.fetch(:secret_key_base))
//    }
    // delegate :hash_function, to: :class

    private:

//     void initialize_values() {
//      if ( new_record? && !value.present?) {
//        this->plain_value = this->class.generate_token_value
//        this->value = hash_function(this->plain_value)
//      }
//    }
  };
}
}
