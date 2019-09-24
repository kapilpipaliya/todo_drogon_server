#pragma once
#include "application_job.h"
#include "caf/all.hpp"
namespace openproj {
namespace worker {
class DeleteUserJob : public caf::event_based_actor, public ApplicationJob {
public:
//   DeleteUserJob(user_id) {
//    this->user_id = user_id
//  }

   void perform() {
//    user.destroy
  }

  private:

   void user() {
//    this->user ||= User.find this->user_id
  }
};
}
}
