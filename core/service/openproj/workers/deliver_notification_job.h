class DeliverNotificationJob : public ApplicationJob {
   DeliverNotificationJob(recipient_id, sender_id) {
    @recipient_id = recipient_id
    @sender_id = sender_id
  }

   void perform() {
    // nothing to do if recipient was deleted in the meantime
    return unless recipient

    mail = User.execute_as(recipient) { build_mail }
    if ( mail) {
      mail.deliver_now
    }
  }

  private:

  // To be implemented by subclasses.
  // Actual recipient and sender User objects are passed (always non-nil).
  // Returns a Mail::Message, or nil if no message should be sent.
   void render_mail(recipient:, sender:) {
    raise 'SubclassResponsibility'
  }

   void build_mail() {
    render_mail(recipient: recipient, sender: sender)
  rescue StandardError => e
    Rails.logger.error "#{this->class.name}: Unexpected error rendering a mail: #{e}"
    // not raising, to avoid re-schedule of DelayedJob; don't expect render errors to fix themselves
    // by retrying
    nil
  }

   void recipient() {
    @recipient ||= User.find_by(id: @recipient_id)
  }

   void sender() {
    @sender ||= User.find_by(id: @sender_id) || DeletedUser.first
  }
}
