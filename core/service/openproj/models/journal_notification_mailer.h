#pragma once
namespace openproj {
namespace models {
class JournalNotificationMailer {
//  class << self {
//     void distinguish_journals(journal, send_notification) {
//      if ( send_notification) {
//        if ( journal.journable_type == 'WorkPackage') {
//          handle_work_package_journal(journal)
//        }
//      }
//    }

//     void handle_work_package_journal(journal) {
//      return nil unless send_notification? journal
//      return nil unless ::UserMailer.perform_deliveries

//      aggregated = find_aggregated_journal_for(journal)

//      // Send the notification on behalf of the predecessor in case it could not send it on its own
//      if ( JournalN::AggregatedJournal.hides_notifications?(aggregated, aggregated.predecessor)) {
//        work_package = aggregated.predecessor.journable
//        notification_receivers(work_package).each { |recipient|
//          job = DeliverWorkPackageNotificationJob.new(aggregated.predecessor.id,
//                                                      recipient.id,
//                                                      User.current.id)
//          Delayed::Job.enqueue job, priority: ::ApplicationJob.priority_number(:notification)
//        }
//      }

//      job = EnqueueWorkPackageNotificationJob.new(journal.id, User.current.id)
//      Delayed::Job.enqueue job,
//                           run_at: delivery_time,
//                           priority: ::ApplicationJob.priority_number(:notification)
//    }

//     void send_notification?(journal) {
//      (Setting.notified_events.include?('work_package_added') && journal.initial?) ||
//        (Setting.notified_events.include?('work_package_updated') && !journal.initial?) ||
//        notify_for_notes?(journal) ||
//        notify_for_status?(journal) ||
//        notify_for_priority(journal)
//    }

//     void notify_for_notes?(journal) {
//      Setting.notified_events.include?('work_package_note_added') && journal.notes.present?
//    }

//     void notify_for_status?(journal) {
//      Setting.notified_events.include?('status_updated') &&
//        journal.details.has_key?(:status_id)
//    }

//     void notify_for_priority(journal) {
//      Setting.notified_events.include?('work_package_priority_updated') &&
//        journal.details.has_key?(:priority_id)
//    }

//     void delivery_time() {
//      Setting.journal_aggregation_time_minutes.to_i.minutes.from_now
//    }

//     void find_aggregated_journal_for(raw_journal) {
//      wp_journals = JournalN::AggregatedJournal.aggregated_journals(journable: raw_journal.journable)
//      wp_journals.detect { |journal| journal.version == raw_journal.version }
//    }

//     void notification_receivers(work_package) {
//      (work_package.recipients + work_package.watcher_recipients).uniq
//    }
//  }
};
}

}