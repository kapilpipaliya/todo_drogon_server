class DeliverInvitationJob : public ApplicationJob {
  attr_reader :token_id

   DeliverInvitationJob(token_id) {
    @token_id = token_id
  }

   void perform() {
    if ( token) {
      UserMailer.user_signed_up(token).deliver_now
    else
      Rails.logger.warn "Can't deliver invitation. The token is missing: #{token_id}"
    }
  }

   void token() {
    @token ||= Token::Invitation.find_by(id: @token_id)
  }
}
