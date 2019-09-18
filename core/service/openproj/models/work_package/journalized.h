#pragma once
namespace openproj {
namespace models {
namespace WorkPackageN::Journalized {
  // extend ActiveSupport::Concern

//  included {
//    acts_as_journalized calculate: -> { { parent_id: parent && parent.id } }

//    // This one is here only to ease reading
//    namespace JournalizedProcs {
//       void event_title() {
//        Proc.new { |o|
//          title = o.to_s
//          title << " (#{o.status.name})" if ( o.status.present?) {

//          title
//        }
//      }

//       void event_name() {
//        Proc.new { |o|
//          I18n.t(o.event_type.underscore, scope: 'events')
//        }
//      }

//       void event_type() {
//        Proc.new { |o|
//          journal = o.last_journal
//          t = 'work_package'

//          t << if ( journal && journal.details.empty? && !journal.initial?) {
//                 '-note'
//               else
//                 status = Status.find_by(id: o.status_id)

//                 status.try(:is_closed?) ? '-closed' : '-edit'
//               }
//          t
//        }
//      }

//       void event_url() {
//        Proc.new { |o|
//          { controller: :work_packages, action: :show, id: o.id }
//        }
//      }
//    }

//    acts_as_event title: JournalizedProcs.event_title,
//                  type: JournalizedProcs.event_type,
//                  name: JournalizedProcs.event_name,
//                  url: JournalizedProcs.event_url

//    register_on_journal_formatter(:id, 'parent_id')
//    register_on_journal_formatter(:fraction, 'estimated_hours')
//    register_on_journal_formatter(:fraction, 'derived_estimated_hours')
//    register_on_journal_formatter(:decimal, 'done_ratio')
//    register_on_journal_formatter(:diff, 'description')
//    register_on_journal_formatter(:attachment, /attachments_?\d+/)
//    register_on_journal_formatter(:custom_field, /custom_fields_\d+/)

//    // Joined
//    register_on_journal_formatter :named_association, :parent_id, :project_id,
//                                  :status_id, :type_id,
//                                  :assigned_to_id, :priority_id,
//                                  :category_id, :fixed_version_id,
//                                  :planning_element_status_id,
//                                  :author_id, :responsible_id
//    register_on_journal_formatter :datetime, :start_date, :due_date
//    register_on_journal_formatter :plaintext, :subject
//  }
}
}
}