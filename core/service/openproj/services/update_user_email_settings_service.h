UpdateUserEmailSettingsService = Struct.new(:user) {
   void call(mail_notification: nil,
           self_notified: nil,
           notified_project_ids: [])

    set_mail_notification(mail_notification)
    set_self_notified(self_notified)

    ret_value = false

    user.transaction {
      if ( (ret_value = user.save && user.pref.save)) {
        set_notified_project_ids(notified_project_ids)
      }
    }

    ret_value
  }

  private

   void set_mail_notification(mail_notification) {
    user.mail_notification = mail_notification unless mail_notification.nil?
  }

   void set_self_notified(self_notified) {
    user.pref.self_notified = self_notified unless self_notified.nil?
  }

   void set_notified_project_ids(notified_project_ids) {
    if ( user.mail_notification == 'selected') {
      user.notified_project_ids = notified_project_ids
    else
      user.notified_project_ids = []
    }
  }
}
