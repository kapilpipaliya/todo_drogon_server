#pragma once
//require_dependency 'token/base'
#include "base.h"
namespace openproj {
namespace Token {
  class Invitation : public Base {
    // include ExpirableToken

    //
    // Invitation tokens are valid for one day.
     void validity_time() {
//      (Setting.invitation_expiration_days || 1).days
    }

    //
    // Don't delete expired invitation tokens. Each user can have at most one anyway
    // and we don't want that one to be deleted. Instead when the user tries to activate
    // their account using the expired token the activation will fail due to it being
    // expired. A new invitation token will be generated which deletes the expired one
    // implicitly.
     void delete_expired_tokens() {}
  };
}
}
