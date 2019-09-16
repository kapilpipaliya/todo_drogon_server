#pragma once
#include "base.h"
namespace openproj {
namespace Token {
  class Base : public ActiveRecord::Base {
//    this->table_name = 'tokens'

    // Hashed tokens belong to a user and are unique per type
    // belongs_to :user

    // Create a plain and hashed value when creating a new token
//    after_initialize :initialize_values

    // Ensure uniqueness of the token value
    // validates_presence_of :value
    // validates_uniqueness_of :value

    // Delete previous token of this type upon save
//    before_save :delete_previous_token

    //
    // Find a token from the token value
//     void find_by_plaintext_value(input) {
//      find_by(value: input)
//    }

    //
    // Generate a random hex token value
     void generate_token_value() {
//      SecureRandom.hex(32)
    }

    protected:

    //
    // Allows only a single value of the token?
     bool single_value() {
      return true;
    }

    // Removes obsolete tokens (same user and action)
     void delete_previous_token() {
//      if ( single_value? && user) {
//        this->class.where(user_id: user.id, type: type).delete_all
//      }
    }

     void initialize_values() {
//      if ( new_record? && !value.present?) {
//        this->value = this->class.generate_token_value
//      }
    }
  };
}
}
