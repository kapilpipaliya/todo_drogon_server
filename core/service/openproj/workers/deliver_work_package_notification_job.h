#pragma once
#include "deliver_notification_job.h"
#include "caf/all.hpp"
namespace openproj {
namespace worker {
class DeliverWorkPackageNotificationJob : public caf::event_based_actor, public DeliverNotificationJob {
public:

//   DeliverWorkPackageNotificationJob(journal_id, recipient_id, author_id) {
//    this->journal_id = journal_id
//    super(recipient_id, author_id)
//  }

//   void render_mail(recipient:, sender:) {
//    return nil unless raw_journal // abort, assuming that the underlying WP was deleted

//    journal = find_aggregated_journal

//    // The caller should have ensured that the journal can"t outdate anymore
//    // before queuing a notification
//    raise "aggregated journal got outdated" unless journal

//    if ( journal.initial?) {
//      UserMailer.work_package_added(recipient, journal, sender)
//    else
//      UserMailer.work_package_updated(recipient, journal, sender)
//    }
//  }

  private:

   void raw_journal() {
//    this->raw_journal ||= Journal.find_by(id: this->journal_id)
  }

   void find_aggregated_journal() {
//    wp_journals = JournalN::AggregatedJournal.aggregated_journals(journable: work_package)
//    wp_journals.detect { |journal| journal.version == raw_journal.version }
  }

   void work_package() {
//    this->work_package ||= raw_journal.journable
  }
};
}
}
