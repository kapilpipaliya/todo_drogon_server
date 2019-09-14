class DeliverWatcherNotificationJob : public DeliverNotificationJob {

   DeliverWatcherNotificationJob(watcher_id, recipient_id, watcher_setter_id) {
    @watcher_id = watcher_id

    super(recipient_id, watcher_setter_id)
  }

   void render_mail(recipient:, sender:) {
    return nil unless watcher

    UserMailer.work_package_watcher_added(watcher.watchable, recipient, sender)
  }

  private:

   void watcher() {
    @watcher ||= Watcher.find_by(id: @watcher_id)
  }
}
