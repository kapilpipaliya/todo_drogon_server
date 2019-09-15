#pragma once
#include "application_job.h"
namespace openproject {
class DeliverInvitationJob : public ApplicationJob {
//  attr_reader :token_id

//   DeliverInvitationJob(token_id) {
//    this->token_id = token_id
//  }

   void perform() {
//    if ( token) {
//      UserMailer.user_signed_up(token).deliver_now
//    else
//      Rails.logger.warn "Can't deliver invitation. The token is missing: #{token_id}"
//    }
  }

   void token() {
//    this->token ||= Token::Invitation.find_by(id: this->token_id)
  }
};
}
