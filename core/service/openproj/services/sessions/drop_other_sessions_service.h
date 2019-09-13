#include "./base_service.h"

namespace Sessions {
  class DropOtherSessionsService : public BaseService {
    class << self
      //
      // Drop all other sessions for the current user.
      // This can only be done when active record sessions are used.
       void call(user, session) {
        return false unless active_record_sessions?

        ::UserSession
          .where(user_id: user.id)
          .where.not(session_id: session.id)
          .delete_all

        true
      }
    }
  }
}
