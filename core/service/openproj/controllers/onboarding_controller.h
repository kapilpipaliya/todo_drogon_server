#include "application_controller.h"
class OnboardingController : public ApplicationController {
   void user_settings() {
    @user = User.current

    result = Users::UpdateService
             .new(current_user: @user)
             .call(permitted_params, params)

    if ( result.success?) {
      flash[:notice] = l(:notice_account_updated)
    }

    // Remove all query params:
    // the first_time_user param so that the modal is not shown again after redirect,
    // the welcome param so that the analytics is not fired again
    uri = Addressable::URI.parse(request.referrer.to_s)
    uri.query_values = {}
    redirect_to uri.to_s
  }
}
