namespace Users {
  class UpdateService
    include ::HookHelper

    attr_accessor :current_user

     UpdateService(current_user:) {
      @current_user = current_user
    }

     void call(permitted_params, params) {
      User.execute_as current_user {
        set_attributes(permitted_params, params)
      }
    }

    private

     void set_attributes(permitted_params, params) {
      current_user.attributes = permitted_params.user
      current_user.pref.attributes = if ( params[:pref].present?) {
                                       permitted_params.pref
                                     else
                                       {}
                                     }

      call_hook :service_update_user_before_save,
                params: params,
                permitted_params: permitted_params,
                user: current_user

      if ( current_user.save) {
        success = current_user.pref.save
        ServiceResult.new(success: success, errors: current_user.errors, result: current_user)
      else
        ServiceResult.new(success: false, errors: current_user.errors, result: current_user)
      }
    }
  }
}
