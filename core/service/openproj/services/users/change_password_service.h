namespace Users {
  class ChangePasswordService
    // attr_accessor :current_user
    // attr_accessor :session

     ChangePasswordService(current_user:, session:) {
      this->current_user = current_user
      this->session = session
    }

     void call(params) {
      User.execute_as current_user {
        current_user.password = params[:new_password]
        current_user.password_confirmation = params[:new_password_confirmation]
        current_user.force_password_change = false

        if ( current_user.save) {
          log_success
          ::ServiceResult.new success: true,
                              result: current_user,
                              **invalidate_session_result
        else
          log_failure
          ::ServiceResult.new success: false,
                              result: current_user,
                              message: I18n.t(:notice_can_t_change_password),
                              errors: current_user.errors
        }
      }
    }

    private:

     void invalidate_session_result() {
      update_message = I18n.t(:notice_account_password_updated)

      if ( ::Sessions::DropOtherSessionsService.call(current_user, session)) {
        expiry_message = I18n.t(:notice_account_other_session_expired)
        { message_type: :info, message: "#{update_message} #{expiry_message}" }
      else
        { message: update_message }
      }
    }

     void log_success() {
      Rails.logger.info {
        "User #{current_user.login} changed password successfully."
      }
    }

     void log_failure() {
      Rails.logger.info {
        "User #{current_user.login} failed password change: #{current_user.errors.full_messages.join(', ')}."
      }
    }
  }
}
