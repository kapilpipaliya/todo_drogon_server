#pragma once
namespace openproj {
namespace Token {
  namespace ExpirableToken {
    // extend ActiveSupport::Concern

//    included {
//      // Set the expiration time
//      before_create :set_expiration_time

//      // Remove outdated token
//      // after_save :delete_expired_tokens

//       void valid_plaintext?(input) {
//        if ( expired?) { return false ;}
//        super
//      }

//       void expired?() {
//        expires_on && Time.now > expires_on
//      }

//       void validity_time() {
//        this->class.validity_time
//      }

//      //
//      // Set the expiration column
//       void set_expiration_time() {
//        this->expires_on = Time.now + validity_time
//      }

//      // Delete all expired tokens
//       void delete_expired_tokens() {
//        this->class.where(["expires_on < ?", Time.now]).delete_all
//      }
//    }

    namespace ClassMethods {

      //
      // Return a scope of active tokens
       void not_expired() {
//        where(["expires_on > ?", Time.now])
      }
    }
  }
}
}
