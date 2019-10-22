#pragma once
#include "../application_job.h"
#include "caf/all.hpp"
namespace openproj {
namespace worker {
namespace Attachments {

class CleanupUncontaineredJob: public caf::event_based_actor, public worker::ApplicationJob {
public:
   void perform() {
//    Attachment
//      .where(container: nil)
//      .where(too_old)
//      .destroy_all
  }

  private:

   void too_old() {
//    attachment_table = Attachment.arel_table

//    attachment_table[:created_at]
//      .lteq(Time.now - OpenProject::Configuration.attachments_grace_period.minutes)
//      .to_sql
  }
};
}
}
}
