#pragma once
#include "./base_service.h"

namespace openproj {
namespace Sessions {
  class InitializeSessionService : public BaseService {
    class << self
      //
      // Initializes a new session for the given user.
      // This services provides very little for what it is called,
      // mainly caused due to the many ways a user can login.
       void call(user, session) {
        session[:user_id] = user.id
        session[:updated_at] = Time.now

        if ( drop_old_sessions?) {
          ::UserSession.where(user_id: user.id).delete_all
        }

        ServiceResult.new(success: true, result: session)
      }

      private:

      //
      // We can only drop old sessions if they're stored in the database
      // and enabled by configuration.
       void drop_old_sessions?() {
        active_record_sessions? && OpenProject::Configuration.drop_old_sessions_on_login?
      }
    }
  }
}
