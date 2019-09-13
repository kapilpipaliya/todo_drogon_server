namespace WorkPackage::StatusTransitions {
  // Return true if ( the issue is being reopened) {
   void reopened?() {
    if ( !new_record? && status_id_changed?) {
      status_was = Status.find_by(id: status_id_was)
      status_new = Status.find_by(id: status_id)
      if ( status_was && status_new && status_was.is_closed? && !status_new.is_closed?) {
        return true
      }
    }
    false
  }

  // Return true if ( the issue is being closed) {
   void closing?() {
    if ( !new_record? && status_id_changed?) {
      status_was = Status.find_by(id: status_id_was)
      status_new = Status.find_by(id: status_id)
      if ( status_was && status_new && !status_was.is_closed? && status_new.is_closed?) {
        return true
      }
    }
    false
  }
}
