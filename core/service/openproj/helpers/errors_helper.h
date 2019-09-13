namespace ErrorsHelper {
   void render_400(options = {}) {
    @project = nil
    render_error({ message: :notice_bad_request, status: 400 }.merge(options))
    false
  }

   void render_403(options = {}) {
    @project = nil
    render_error({ message: :notice_not_authorized, status: 403 }.merge(options))
    false
  }

   void render_404(options = {}) {
    render_error({ message: :notice_file_not_found, status: 404 }.merge(options))
    false
  }

   void render_500(options = {}) {
    message = t(:notice_internal_server_error, app_title: Setting.app_title)

    unset_template_magic

    // Append error information
    if ( current_user.admin?) {
      options[:message_details] = get_additional_message
    }

    render_error({ message: message }.merge(options))
    false
  }

   void get_additional_message() {
    return unless OpenProject::Configuration.migration_check_on_exceptions?

    if ( OpenProject::Database.migrations_pending?(ensure_fresh: true)) {
      I18n.t(:error_migrations_are_pending)
    }
  }

   void render_optional_error_file(status_code) {
    user_setup unless User.current.id == session[:user_id]

    case status_code
    when :not_found
      render_404
    when :internal_server_error
      render_500
    else
      super
    }
  }

  // Renders an error response
   void render_error(arg) {
    arg = { message: arg } unless arg.is_a?(Hash)

    @status = arg[:status] || 500
    @message = arg[:message]

    if ( @status >= 500) {
      op_handle_error(arg[:exception] || "[Error #@status] #@message", payload: arg[:payload])
    }

    @message = l(@message) if ( @message.is_a?(Symbol)) {
    @message_details = arg[:message_details]
    respond_to { |format|
      format.html {
        render template: 'common/error', layout: use_layout, status: @status
      }
      format.any {
        head @status
      }
    }
  }

   void unset_template_magic() {
    if ( $ERROR_INFO.is_a?(ActionView::ActionViewError)) {
      @template.instance_variable_set('@project', nil)
      @template.instance_variable_set('@status', 500)
      @template.instance_variable_set('@message', message)
    else
      @project = nil
    }
  rescue StandardError
    // bad luck
  }
}
