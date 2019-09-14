//
// Create journal for the given user and note.
// Does not change the work package itself.

namespace openproject {
class AddWorkPackageNoteService
  // include Concerns::Contracted
  // attr_accessor :user, :work_package

   AddWorkPackageNoteService(user:, work_package:) {
    this->user = user
    this->work_package = work_package
    this->contract_class = WorkPackages::CreateNoteContract
  }

   void call(notes, send_notifications: true) {
    JournalManager.with_send_notifications send_notifications {
      work_package.add_journal(user, notes)

      success, errors = validate_and_yield(work_package, user) {
        work_package.save_journals
      }

      if ( success) { journal = work_package.journals.last ;}
      ServiceResult.new(success: success, result: journal, errors: errors)
    }
  }
}
