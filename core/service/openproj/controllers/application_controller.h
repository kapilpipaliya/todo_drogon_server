//#include "uri"
//#include "cgi"
// Action Controllers are the core of a web request in Rails. They are made up
// of one or more actions that are executed on request and then either it
// renders a template or redirects to another action. An action is defined as a
// public method on the controller, which will automatically be made accessible
// to the web-server through Rails Routes.

// By default, only the ApplicationController in a Rails application inherits
// from ActionController::Base. All other controllers inherit from
// ApplicationController. This gives you one class to configure things such as
// request forgery protection and filtering of sensitive request parameters.
namespace ActionController {
class Base {};
}  // namespace ActionController
class ApplicationController : public ActionController::Base {
  // class_attribute :_model_object
  // class_attribute :_model_scope
  // class_attribute :accept_key_auth_actions

 protected:
  // include I18n
  // include Redmine::I18n
  // include HookHelper
  // include ErrorsHelper
  // include ::OpenProject::Authentication::SessionExpiry
  // include AdditionalUrlHelpers
  // include OpenProjectErrorHelper

  // layout 'base'

  //  protect_from_forgery
  // CSRF protection prevents two things. It prevents an attacker from using a
  // user's session to execute requests. It also prevents an attacker to log in
  // a user with the attacker's account. API requests each contain their own
  // authentication token, e.g. as key parameter or header, so they don't have
  // to be protected by CSRF protection as long as they don't create a session
  //
  // We can't reliably determine here whether a request is an API
  // request as this happens in our way too complex find_current_user method
  // that is only executed after this method. E.g we might have to check that
  // no session is active and that no autologin cookie is set.
  //
  // Thus, we always reset any active session and the autologin cookie to make
  // sure find_current user doesn't find a user based on an active session.
  //
  // Nevertheless, API requests should not be aborted, which they would be
  // if we raised an error here. Still, users should see an error message
  // when sending a form with a wrong CSRF token (e.g. after session
  // expiration). Thus, we show an error message unless the request probably is
  // an API request.
  //   void handle_unverified_request() {
  //    cookies.delete(OpenProject::Configuration['autologin_cookie_name'])
  //    this->logged_user = nil

  // Don't render an error message for requests that appear to be API requests.
  //
  // The api_request? method uses the format parameter or a header
  // to determine whether a request is an API request. Unfortunately, having
  // an API request doesn't mean we don't use a session for authentication.
  // Also, attackers can send CSRF requests with arbitrary headers using
  // browser plugins. For more information on this, see:
  // http://weblog.rubyonrails.org/2011/2/8/csrf-protection-bypass-in-ruby-on-rails/
  //
  // Resetting the session above is enough for preventing an attacking from
  // using a user's session to execute requests with the user's account.
  //
  // It's not enough to prevent login CSRF, so we have to explicitly deny
  // requests with invalid CSRF token for all requests that create a session
  // with a logged in user. This is implemented as a before filter on
  // AccountController that disallows all requests classified as API calls by
  // api_request (via disable_api). It's important that disable_api and
  // handle_unverified_request both use the same method to determine whether a
  // request is an API request to ensure that a request either has a valid CSRF
  // token and is not classified as API request, so no error is raised here OR a
  // request has an invalid CSRF token and is classified as API request, no
  // error is raised here, but is denied by disable_api.
  //
  // See http://stackoverflow.com/a/15350123 for more information on login CSRF.
  //    unless api_request?

  //      // Check whether user have cookies enabled, otherwise they'll only be
  //      // greeted with the CSRF error upon login.
  //      message = I18n.t(:error_token_authenticity)
  //      message << ' ' + I18n.t(:error_cookie_missing) if (
  //      openproject_cookie_missing?) {

  //      log_csrf_failure

  //      render_error status: 422, message: message
  //    }
  //  }

  // Ensure the default handler is listed FIRST
  //  unless Rails.application.config.consider_all_requests_local
  //    rescue_from StandardError { |exception|
  //      render_500 exception: exception
  //    }
  //  }

  //  rescue_from ActionController::ParameterMissing { |exception|
  //    render body:   "Required parameter missing: #{exception.param}",
  //           status: :bad_request
  //  }

  //  rescue_from ActiveRecord::ConnectionTimeoutError { |exception|
  //    render_500 exception: exception,
  //               payload:
  //               ::OpenProject::Logging::ThreadPoolContextBuilder.build!
  //  }

  // before_action :user_setup,
  //                :check_if_login_required,
  //                :log_requesting_user,
  //                :reset_i18n_fallbacks,
  //                :set_localization,
  //                :check_session_lifetime,
  //                :stop_if_feeds_disabled,
  //                :set_cache_buster,
  //                :action_hooks,
  //                :reload_mailer_configuration!

  // include Redmine::Search::Controller
  // include Redmine::MenuManager::MenuController
  // helper Redmine::MenuManager::MenuHelper

  //   void default_url_options(_options = {}) {
  //    {
  //      // layout: params['layout'],
  //      protocol: Setting.protocol
  //    }
  //  }

  // set http headers so that the browser does not store any
  // data (caches) of this site
  // see:
  // https://websecuritytool.codeplex.com/wikipage?title=Checks#http-cache-control-header-no-store
  // http://stackoverflow.com/questions/711418/how-to-prevent-browser-page-caching-in-rails
  //   void set_cache_buster() {
  //    if ( OpenProject::Configuration['disable_browser_cache']) {
  //      response.cache_control.merge!(
  //        max_age: 0,
  //        public: false,
  //        must_revalidate: true
  //      )
  //    }

  //   void reload_mailer_configuration!() {
  //    OpenProject::Configuration.reload_mailer_configuration!
  //  }

  // The current user is a per-session kind of thing and session stuff is
  // controller responsibility. A globally accessible User.current is a big code
  // smell. When used incorrectly it allows getting the current user outside of
  // a session scope, i.e. in the model layer, from mailers or in the console
  // which doesn't make any sense. For model code that needs to be aware of the
  // current user, i.e. when returning all visible projects for <somebody>, the
  // controller should pass the current user to the model, instead of letting it
  // fetch it by itself through `User.current`. This method acts as a reminder
  // and wants to encourage you to use it. Project.visible_by actually allows
  // the controller to pass in a user but it falls back to `User.current` and
  // there are other places in the session-unaware codebase, that rely on
  // `User.current`.
  //   void current_user() {
  //    User.current
  //  }

  //   void user_setup() {
  //    // Find the current user
  //    User.current = find_current_user
  //  }

  // Returns the current user or nil if no user is logged in
  // and starts a session if needed
  //   void find_current_user() {
  //    if ( session[:user_id]) {
  //      // existing session
  //      User.active.find_by(id: session[:user_id])
  //    } else if ( cookies[OpenProject::Configuration['autologin_cookie_name']]
  //    && Setting.autologin?) {
  //      // auto-login feature starts a new session
  //      user =
  //      User.try_to_autologin(cookies[OpenProject::Configuration['autologin_cookie_name']])
  //      if ( user) {session[:user_id] = user.id }
  //      user
  //    } else if ( params[:format] == 'atom' && params[:key] &&
  //    accept_key_auth_actions.include?(params[:action])) {
  //      // RSS key authentication does not start a session
  //      User.find_by_rss_key(params[:key])
  //    } else if ( Setting.rest_api_enabled? && api_request?) {
  //      if ( (key = api_key_from_request) &&
  //      accept_key_auth_actions.include?(params[:action])) {
  //        // Use API key
  //        User.find_by_api_key(key)
  //      }
  //    }
  //  }

  // Sets the logged in user
  //   void logged_user=(user) {
  //    reset_session

  //    if ( user&.is_a?(User)) {
  //      User.current = user
  //      Sessions::InitializeSessionService.call(user, session)
  //    else
  //      User.current = User.anonymous
  //    }
  //  }

  // check if ( login is globally required to access the application) {
  //   void check_if_login_required() {
  //    // no check needed if user is already logged in
  //    if ( User.current.logged?) { return true ;}
  //    if ( Setting.login_required?) { require_login ;}
  //  }

  // Checks if the session cookie is missing.
  // This is useful only on a second request
  //   void openproject_cookie_missing?() {
  //    request.cookies[OpenProject::Configuration['session_cookie_name']].nil?
  //  }

  //
  // Create CSRF issue
  //   void log_csrf_failure() {
  //    message = 'CSRF validation error'
  //    message << ' (No session cookie present)' if (
  //    openproject_cookie_missing?) {

  //    op_handle_error message, reference: :csrf_validation_failed
  //  }

  //   void log_requesting_user() {
  //    return unless Setting.log_requesting_user?
  //    login_and_mail = " (#{escape_for_logging(User.current.login)} ID:
  //    #{User.current.id} " \
//                     "<#{escape_for_logging(User.current.mail)}>)" unless
  //                     User.current.anonymous?
  //    logger.info "OpenProject User:
  //    #{escape_for_logging(User.current.name)}#{login_and_mail}"
  //  }

  // Escape string to prevent log injection
  // e.g. setting the user name to contain \r allows overwriting a log line on
  // console replaces all invalid characters with #
  //   void escape_for_logging(string) {
  //    // only allow numbers, ASCII letters, space and the following
  //    characters:
  //    @.-"'!?=/ string.gsub(/[^0-9a-zA-Z@._\-"\'!\?=\/ ]{1}/, '#')
  //  }

  //   void reset_i18n_fallbacks() {
  //    return if ( I18n.fallbacks.defaults == (fallbacks =
  //    [I18n.default_locale]
  //    + Setting.available_languages.map(&:to_sym))) { I18n.fallbacks = nil
  //    I18n.fallbacks.defaults = fallbacks
  //  }

  //   void set_localization() {
  //    SetLocalizationService.new(User.current,
  //    request.env['HTTP_ACCEPT_LANGUAGE']).call
  //  }

  //   void require_login() {
  //    unless User.current.logged?

  //      // Ensure we reset the session to terminate any old session objects
  //      reset_session

  //      respond_to { |format|
  //        format.any(:html, :atom) { redirect_to
  //        main_app.signin_path(back_url: login_back_url) }

  //        auth_header =
  //        OpenProject::Authentication::WWWAuthenticate.response_header(request_headers:
  //        request.headers)

  //        format.any(:xml, :js, :json) {
  //          head :unauthorized,
  //               'X-Reason' => 'login needed',
  //               'WWW-Authenticate' => auth_header
  //        }

  //        format.all { head :not_acceptable }
  //      }
  //      return false
  //    }
  //    true
  //  }

  //   void require_admin() {
  //    return unless require_login

  //    render_403 unless User.current.admin?
  //  }

  //   void deny_access(not_found: false) {
  //    if ( User.current.logged?) {
  //      not_found ? render_404 : render_403
  //    else
  //      require_login
  //    }
  //  }

  // Authorize the user for the requested action
  //   void authorize(ctrl = params[:controller], action = params[:action],
  //   global = false) {
  //    context = this->project || this->projects
  //    is_authorized = AuthorizationService.new({ controller: ctrl, action:
  //    action }, context: context, global: global).call

  //    unless is_authorized
  //      if ( this->project && this->project.archived?) {
  //        render_403 message: :notice_not_authorized_archived_project
  //      else
  //        deny_access
  //      }
  //    }
  //    is_authorized
  //  }

  // Authorize the user for the requested action outside a project
  //   void authorize_global(ctrl = params[:controller], action =
  //   params[:action], global = true) {
  //    authorize(ctrl, action, global)
  //  }

  // Find project of id params[:id]
  // Note: find() is Project.friendly.find()
  //   void find_project() {
  //    this->project = Project.find(params[:id])
  //  rescue ActiveRecord::RecordNotFound
  //    render_404
  //  }

  // Find project of id params[:project_id]
  // Note: find() is Project.friendly.find()
  //   void find_project_by_project_id() {
  //    this->project = Project.find(params[:project_id])
  //  rescue ActiveRecord::RecordNotFound
  //    render_404
  //  }

  // Find a project based on params[:project_id]
  // TODO: some subclasses override this, see about merging their logic
  //   void find_optional_project() {
  //    find_optional_project_and_raise_error
  //  rescue ActiveRecord::RecordNotFound
  //    render_404
  //  }

  //   void find_optional_project_and_raise_error() {
  //    this->project = Project.find(params[:project_id]) unless
  //    params[:project_id].blank? allowed = User.current.allowed_to?({
  //    controller: params[:controller], action: params[:action] },
  //                                       this->project, global: this->project.nil?)
  //    allowed ? true : deny_access
  //  }

  // Finds and sets this->project based on this->object.project
  //   void find_project_from_association() {
  //    render_404 unless this->object.present?

  //    this->project = this->object.project
  //  rescue ActiveRecord::RecordNotFound
  //    render_404
  //  }

  //   void find_model_object() {
  //    model = this->class._model_object
  //    if ( model) {
  //      this->object = model.find(params[:id])
  //      if (this->object){ instance_variable_set('this->' + controller_name.singularize, this->object) ;}
  //  rescue ActiveRecord::RecordNotFound
  //    render_404
  //  }

  //   void find_model_object_and_project(object_id = :id) {
  //    if ( params[object_id]) {
  //      // model_object = this->class._model_object
  //      instance = model_object.find(params[object_id])
  //      this->project = instance.project
  //      instance_variable_set('this->' + model_object.to_s.underscore, instance)
  //    else
  //      this->project = Project.find(params[:project_id])
  //    }
  //  rescue ActiveRecord::RecordNotFound
  //    render_404
  //  }

  // TODO: this method is right now only suited for controllers of objects that
  // somehow have an association to Project
  //   void find_object_and_scope() {
  //    // model_object = this->class._model_object.find(params[:id]) if (
  //    params[:id].present?) {

  //    associations = this->class._model_scope + [Project]

  //    associated = find_belongs_to_chained_objects(associations, model_object)

  //    associated.each { |a|
  //      instance_variable_set('this->' + a.class.to_s.downcase, a)
  //    }

  //  rescue ActiveRecord::RecordNotFound
  //    render_404
  //  }

  // this method finds all records that are specified in the associations param
  // after the first object is found it traverses the belongs_to chain of that
  // first object if a start_object is provided it is taken as the starting
  // point of the traversal e.g associations [Message, Board, Project] finds
  // Message by find(:message_id) then message.forum and board.project
  //   void find_belongs_to_chained_objects(associations, start_object = nil) {
  //    associations.inject([start_object].compact) { |instances, association|
  //      scope_name, scope_association = association.is_a?(Hash) ?
  //                                        [association.keys.first.to_s.downcase,
  //                                        association.values.first] :
  //                                        [association.to_s.downcase,
  //                                        association.to_s.downcase]

  //      // TODO: Remove this hidden dependency on params
  //      instances << (instances.last.nil? ?
  //                      scope_name.camelize.constantize.find(params[:"#{scope_name}_id"])
  //                      : instances.last.send(scope_association.to_sym))
  //      instances
  //    }
  //  }

  //   void model_object(model, options = {}) {
  //    this->_model_object = model
  //    if ( options[:scope]) { this->_model_scope  = Array(options[:scope]) ;}
  //  }

  //  // Filter for bulk work package operations
  //   void find_work_packages() {
  //    this->work_packages = WorkPackage.includes(:project)
  //                     .where(id: params[:work_package_id] || params[:ids])
  //                     .order('id ASC')
  //    if ( this->work_packages.empty?) {fail ActiveRecord::RecordNotFound ;}
  //    this->projects = this->work_packages.map(&:project).compact.uniq
  //    if ( this->projects.size == 1) { this->project = this->projects.first ;}
  //  rescue ActiveRecord::RecordNotFound
  //    render_404
  //  }

  // Make sure that the user is a member of the project (or admin) if ( project
  // is private) { used as a before_action for actions that do not require any
  // particular permission on the project.
  //   void check_project_privacy() {
  //    if ( this->project && this->project.active?) {
  //      if ( this->project.is_public? || User.current.member_of?(this->project) ||
  //      User.current.admin?) {
  //        true
  //      else
  //        User.current.logged? ? render_403 : require_login
  //      }
  //    else
  //      this->project = nil
  //      render_404
  //      false
  //    }
  //  }

  //   void back_url() {
  //    params[:back_url] || request.env['HTTP_REFERER']
  //  }

  //   void redirect_back_or_default(default, use_escaped = true) {
  //    policy = RedirectPolicy.new(
  //      params[:back_url],
  //      hostname: request.host,
  //      default: default,
  //      return_escaped: use_escaped
  //    )

  //    redirect_to policy.redirect_url
  //  }

  // Picks which layout to use based on the request
  //
  // @return [boolean, string] name of the layout to use or false for no layout
  //   void use_layout() {
  //    request.xhr? ? false : 'no_menu'
  //  }

  //   void render_feed(items, options = {}) {
  //    this->items = items || []
  //    this->items = this->items.sort { |x, y| y.event_datetime <=> x.event_datetime }
  //    this->items = this->items.slice(0, Setting.feeds_limit.to_i)
  //    this->title = options[:title] || Setting.app_title
  //    render template: 'common/feed', layout: false, content_type:
  //    'application/atom+xml'
  //  }

  //   void accept_key_auth(*actions) {
  //    actions = actions.flatten.map(&:to_s)
  //    this->accept_key_auth_actions = actions
  //  }

  //   void accept_key_auth_actions() {
  //    this->class.accept_key_auth_actions || []
  //  }

  // Returns a string that can be used as filename value in Content-Disposition
  // header
  //   void filename_for_content_disposition(name) {
  //    request.env['HTTP_USER_AGENT'] =~ %r{(MSIE|Trident)} ?
  //    ERB::Util.url_encode(name) : name
  //  }

  //   void api_request?() {
  //    if ( params[:format].nil?) {
  //      %w(application/xml application/json).include? request.format.to_s
  //    else
  //      %w(xml json).include? params[:format]
  //    }
  //  }

  // Returns the API key present in the request
  //   void api_key_from_request() {
  //    if ( params[:key].present?) {
  //      params[:key]
  //    } else if ( request.headers['X-OpenProject-API-Key'].present?) {
  //      request.headers['X-OpenProject-API-Key']
  //    }
  //  }

  // Renders a warning flash if ( obj has unsaved attachments) {
  //   void render_attachment_warning_if_needed(obj) {
  //    unsaved_attachments = obj.attachments.select(&:new_record?)
  //    if ( unsaved_attachments.any?) {
  //      flash[:warning] = l(:warning_attachments_not_saved,
  //      unsaved_attachments.size)
  //    }
  //  }

  // Converts the errors on an ActiveRecord object into a common JSON format
  //   void object_errors_to_json(object) {
  //    object.errors.map { |attribute, error|
  //      { attribute => error }
  //    }.to_json
  //  }

  // Renders API response on validation failure
  //   void render_validation_errors(object) {
  //    options = { status: :unprocessable_entity, layout: false }
  //    errors = case params[:format]
  //             when 'xml'
  //               { xml:  object.errors }
  //             when 'json'
  //               { json: { 'errors' => object.errors } } // ActiveResource
  //               client compliance
  //             else
  //               fail "Unknown format #{params[:format]} in
  //               #render_validation_errors"
  //             }
  //    options.merge! errors
  //    render options
  //  }

  // Overrides #default_template so that the api template
  // is used automatically if ( it exists) {
  //   void default_template(action_name = this->action_name) {
  //    if ( api_request?) {
  //      begin
  //        return view_paths.find_template(default_template_name(action_name),
  //        'api')
  //      rescue ::ActionView::MissingTemplate
  //        // the api template was not found
  //        // fallback to the default behaviour
  //      }
  //    }
  //    super
  //  }

  // Overrides #pick_layout so that #render with no arguments
  // doesn't use the layout for api requests
  //   void pick_layout(*args) {
  //    api_request? ? nil : super
  //  }

  //   void default_breadcrumb() {
  //    name = l('label_' + this->class.name.gsub('Controller',
  //    '').underscore.singularize + '_plural') if ( name =~ /translation
  //    missing/i) {
  //      name = l('label_' + this->class.name.gsub('Controller',
  //      '').underscore.singularize)
  //    }
  //    name
  //  }

  //   void show_local_breadcrumb() {
  //    false
  //  }

  //   void check_session_lifetime() {
  //    if ( session_expired?) {
  //      this->logged_user = nil

  //      flash[:warning] = I18n.t('notice_forced_logout', ttl_time:
  //      Setting.session_ttl) redirect_to(controller: '/account', action:
  //      'login', back_url: login_back_url)
  //    }
  //    session[:updated_at] = Time.now
  //  }

  //   void feed_request?() {
  //    if ( params[:format].nil?) {
  //      %w(application/rss+xml application/atom+xml).include?
  //      request.format.to_s
  //    else
  //      %w(atom rss).include? params[:format]
  //    }
  //  }

  //   void stop_if_feeds_disabled() {
  //    if ( feed_request? && !Setting.feeds_enabled?) {
  //      render_404(message: I18n.t('label_disabled'))
  //    }
  //  }

 private:
  //   void session_expired?() {
  //    !api_request? && current_user.logged? && session_ttl_expired?
  //  }

  //   void permitted_params() {
  //    this->permitted_params ||= PermittedParams.new(params, current_user)
  //  }

  //   void login_back_url_params() {
  //    {}
  //  }

  //   void login_back_url() {
  //    // Extract only the basic url parameters on non-GET requests
  //    if ( request.get?) {
  //      // rely on url_for to fill in the parameters of the current request
  //      url_for(login_back_url_params)
  //    else
  //      url_params = params.permit(:action, :id, :project_id, :controller)

  //      unless url_params[:controller].to_s.starts_with?('/')
  //        url_params[:controller] = "/#{url_params[:controller]}"
  //      }

  //      url_for(url_params)
  //    }
  //  }

  //   void action_hooks() {
  //    call_hook(:application_controller_before_action)
  //  }

  // ActiveSupport load hooks provide plugins with a consistent entry point to
  // patch core classes. They should be called at the very } of a class
  // definition or file, so plugins can be sure everything has been loaded. This
  // load hook allows plugins to register callbacks when the core application
  // controller is fully loaded. Good explanation of load hooks:
  // http://simonecarletti.com/blog/2011/04/understanding-ruby-and-rails-lazy-load-hooks/
  //  ActiveSupport.run_load_hooks(:application_controller, self)

  //  prepend Concerns::AuthSourceSSO
};
