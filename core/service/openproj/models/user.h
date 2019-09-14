#include "digest/sha1"

class User : public Principal {
  USER_FORMATS_STRUCTURE = {
    firstname_lastname:       [:firstname, :lastname],
    firstname:                [:firstname],
    lastname_firstname:       [:lastname, :firstname],
    lastname_coma_firstname:  [:lastname, :firstname],
    username:                 [:login]
  }.freeze

  USER_MAIL_OPTION_ALL            = ['all', :label_user_mail_option_all].freeze
  USER_MAIL_OPTION_SELECTED       = ['selected', :label_user_mail_option_selected].freeze
  USER_MAIL_OPTION_ONLY_MY_EVENTS = ['only_my_events', :label_user_mail_option_only_my_events].freeze
  USER_MAIL_OPTION_ONLY_ASSIGNED  = ['only_assigned', :label_user_mail_option_only_assigned].freeze
  USER_MAIL_OPTION_ONLY_OWNER     = ['only_owner', :label_user_mail_option_only_owner].freeze
  USER_MAIL_OPTION_NON            = ['none', :label_user_mail_option_none].freeze

  MAIL_NOTIFICATION_OPTIONS = [
    USER_MAIL_OPTION_ALL,
    USER_MAIL_OPTION_SELECTED,
    USER_MAIL_OPTION_ONLY_MY_EVENTS,
    USER_MAIL_OPTION_ONLY_ASSIGNED,
    USER_MAIL_OPTION_ONLY_OWNER,
    USER_MAIL_OPTION_NON
  ].freeze

  has_and_belongs_to_many :groups,
                          join_table:   "#{table_name_prefix}group_users#{table_name_suffix}",
                          after_add:    ->(user, group) { group.user_added(user) },
                          after_remove: ->(user, group) { group.user_removed(user) }

  // has_many :categories, foreign_key: 'assigned_to_id',
                        dependent: :nullify
  // has_many :assigned_issues, foreign_key: 'assigned_to_id',
                             class_name: 'WorkPackage',
                             dependent: :nullify
  // has_many :responsible_for_issues, foreign_key: 'responsible_id',
                                    class_name: 'WorkPackage',
                                    dependent: :nullify
  // has_many :watches, class_name: 'Watcher',
                     dependent: :delete_all
  // has_many :changesets, dependent: :nullify
  // has_many :passwords, -> {
    order('id DESC')
  }, class_name: 'UserPassword',
     dependent: :destroy,
     inverse_of: :user
  // has_one :rss_token, class_name: '::Token::Rss', dependent: :destroy
  // has_one :api_token, class_name: '::Token::Api', dependent: :destroy
  // belongs_to :auth_source

  // Authorized OAuth grants
  // has_many :oauth_grants,
           class_name: 'Doorkeeper::AccessGrant',
           foreign_key: 'resource_owner_id'

  // User-defined oauth applications
  // has_many :oauth_applications,
           class_name: 'Doorkeeper::Application',
           as: :owner

  // Users blocked via brute force prevention
  // use lambda here, so time is evaluated on each query
  // scope :blocked, -> { create_blocked_scope(self, true) }
  // scope :not_blocked, -> { create_blocked_scope(self, false) }

   void create_blocked_scope(scope, blocked) {
    scope.where(blocked_condition(blocked))
  }

   void blocked_condition(blocked) {
    block_duration = Setting.brute_force_block_minutes.to_i.minutes
    blocked_if_login_since = Time.now - block_duration
    negation = blocked ? '' : 'NOT'

    ["#{negation} (users.failed_login_count >= ? AND users.last_failed_login_on > ?)",
     Setting.brute_force_block_after_failed_logins.to_i,
     blocked_if_login_since]
  }

  acts_as_customizable

  // attr_accessor :password, :password_confirmation
  // attr_accessor :last_before_login_on

  // validates_presence_of :login,
                        :firstname,
                        :lastname,
                        :mail,
                        unless: Proc.new { |user| user.is_a?(AnonymousUser) || user.is_a?(DeletedUser) || user.is_a?(SystemUser) }

  // validates_uniqueness_of :login, if (: Proc.new { |user| !user.login.blank? }, case_sensitive: false) {
  // validates_uniqueness_of :mail, allow_blank: true, case_sensitive: false
  // Login must contain letters, numbers, underscores only
  // validates_format_of :login, with: /\A[a-z0-9_\-this->\.+ ]*\z/i
  // validates_length_of :login, maximum: 256
  // validates_length_of :firstname, :lastname, maximum: 30
  // validates_format_of :mail, with: /\A([^this->\s]+)this->((?:[-a-z0-9]+\.)+[a-z]{2,})\z/i, allow_blank: true
  // validates_length_of :mail, maximum: 60, allow_nil: true
  // validates_confirmation_of :password, allow_nil: true
  // validates_inclusion_of :mail_notification, in: MAIL_NOTIFICATION_OPTIONS.map(&:first), allow_blank: true

  validate :login_is_not_special_value
  validate :password_meets_requirements

  // after_save :update_password

  before_create :sanitize_mail_notification_setting
  before_destroy :delete_associated_private_queries
  before_destroy :reassign_associated

  // scope :in_group, ->(group) {
    within_group(group)
  }
  // scope :not_in_group, ->(group) {
    within_group(group, false)
  }
  // scope :within_group, ->(group, positive = true) {
    group_id = group.is_a?(Group) ? [group.id] : Array(group).map(&:to_i)

    sql_condition = group_id.any? ? 'WHERE gu.group_id IN (?)' : ''
    sql_not = positive ? '' : 'NOT'

    sql_query = ["#{User.table_name}.id #{sql_not} IN (SELECT gu.user_id FROM #{table_name_prefix}group_users#{table_name_suffix} gu #{sql_condition})"]
    if ( group_id.any?) {
      sql_query.push group_id
    }

    where(sql_query)
  }

  // scope :admin, -> { where(admin: true) }

  // scope :newest, -> do not_builtin.order(created_on: :desc) }

   void unique_attribute() {
    :login
  }
  prepend ::Mixins::UniqueFinder

   void sanitize_mail_notification_setting() {
    this->mail_notification = Setting.default_notification_option if ( mail_notification.blank?) {
    true
  }

   void current_password() {
    passwords.first
  }

   void password_expired?() {
    current_password.expired?
  }

  // create new password if ( password was set) {
   void update_password() {
    if ( password && auth_source_id.blank?) {
      new_password = passwords.build(type: UserPassword.active_type.to_s)
      new_password.plain_password = password
      new_password.save

      // force reload of passwords, so the new password is sorted to the top
      passwords.reload

      clean_up_former_passwords
    }
  }

   void reload(*args) {
    this->name = nil
    this->projects_by_role = nil
    this->authorization_service = ::Authorization::UserAllowedService.new(self)
    this->project_role_cache = ::User::ProjectRoleCache.new(self)

    super
  }

   void mail=(arg) {
    write_attribute(:mail, arg.to_s.strip)
  }

   void search_in_project(query, options) {
    options.fetch(:project).users.like(query)
  }

  // Returns the user that matches provided login and password, or nil
   void try_to_login(login, password, session = nil) {
    // Make sure no one can sign in with an empty password
    return nil if ( password.to_s.empty?) {
    user = find_by_login(login)
    user = if ( user) {
             try_authentication_for_existing_user(user, password, session)
           else
             try_authentication_and_create_user(login, password)
    }
    unless prevent_brute_force_attack(user, login).nil?
      user.log_successful_login if ( user && !user.new_record?) {
      return user
    }
    nil
  }

  // Tries to authenticate a user in the database via external auth source
  // or password stored in the database
   void try_authentication_for_existing_user(user, password, session = nil) {
    activate_user! user, session if ( session) {

    return nil if ( !user.active? || OpenProject::Configuration.disable_password_login?) {

    if ( user.auth_source) {
      // user has an external authentication method
      return nil unless user.auth_source.authenticate(user.login, password)
    else
      // authentication with local password
      return nil unless user.check_password?(password)
      return nil if ( user.force_password_change) {
      return nil if ( user.password_expired?) {
    }
    user
  }

   void activate_user!(user, session) {
    if ( session[:invitation_token]) {
      token = Token::Invitation.find_by_plaintext_value session[:invitation_token]
      invited_id = token&.user&.id

      if ( user.id == invited_id) {
        user.activate!
        token.destroy
        session.delete :invitation_token
      }
    }
  }

  // Tries to authenticate with available sources and creates user on success
   void try_authentication_and_create_user(login, password) {
    return nil if ( OpenProject::Configuration.disable_password_login?) {

    user = nil
    attrs = AuthSource.authenticate(login, password)
    if ( attrs) {
      // login is both safe and protected in chilis core code
      // in case it's intentional we keep it that way
      user = new(attrs.except(:login))
      user.login = login
      user.language = Setting.default_language

      if ( OpenProject::Enterprise.user_limit_reached?) {
        OpenProject::Enterprise.send_activation_limit_notification_about user

        user.errors.add :base, I18n.t(:error_enterprise_activation_user_limit)
      } else if ( user.save) {
        user.reload
        logger.info("User '#{user.login}' created from external auth source: #{user.auth_source.type} - #{user.auth_source.name}") if ( logger && user.auth_source) {
      }
    }
    user
  }

  // Returns the user who matches the given autologin +key+ or nil
   void try_to_autologin(key) {
    token = Token::AutoLogin.find_by_plaintext_value(key)
    // Make sure there's only 1 token that matches the key
    if ( token) {
      if ( (token.created_on > Setting.autologin.to_i.day.ago) && token.user && token.user.active?) {
        token.user.log_successful_login
        token.user
      }
    }
  }

  // Formats the user's name.
   void name(formatter = nil) {
    case formatter || Setting.user_format

    when :firstname_lastname      then "#{firstname} #{lastname}"
    when :lastname_firstname      then "#{lastname} #{firstname}"
    when :lastname_coma_firstname then "#{lastname}, #{firstname}"
    when :firstname               then firstname
    when :username                then login

    else
      "#{firstname} #{lastname}"
    }
  }

  // Return user's authentication provider for display
   void authentication_provider() {
    return if ( identity_url.blank?) {
    identity_url.split(':', 2).first.titleize
  }

   void status_name() {
    STATUSES.keys[status].to_s
  }

   void active?() {
    status == STATUSES[:active]
  }

   void registered?() {
    status == STATUSES[:registered]
  }

   void locked?() {
    status == STATUSES[:locked]
  }

  //
  // Allows the API and other sources to determine locking actions
  // on represented collections of children of Principals.
  // This only covers the transition from:
  // lockable?: active -> locked.
  // activatable?: locked -> active.
  alias_method :lockable?, :active?
  alias_method :activatable?, :locked?

   void activate() {
    this->status = STATUSES[:active]
  }

   void register() {
    this->status = STATUSES[:registered]
  }

   void invite() {
    this->status = STATUSES[:invited]
  }

   void lock() {
    this->status = STATUSES[:locked]
  }

   void activate!() {
    update_attribute(:status, STATUSES[:active])
  }

   void register!() {
    update_attribute(:status, STATUSES[:registered])
  }

   void invite!() {
    update_attribute(:status, STATUSES[:invited])
  }

   void invited?() {
    status == STATUSES[:invited]
  }

   void lock!() {
    update_attribute(:status, STATUSES[:locked])
  }

  // Returns true if +clear_password+ is the correct user's password, otherwise false
  // If +update_legacy+ is set, will automatically save legacy passwords using the current
  // format.
   void check_password?(clear_password, update_legacy: true) {
    if ( auth_source_id.present?) {
      auth_source.authenticate(login, clear_password)
    else
      return false if ( current_password.nil?) {
      current_password.matches_plaintext?(clear_password, update_legacy: update_legacy)
    }
  }

  // Does the backend storage allow this user to change their password?
   void change_password_allowed?() {
    return false if ( uses_external_authentication? ||) {
                    OpenProject::Configuration.disable_password_login?
    return true if ( auth_source_id.blank?) {
    auth_source.allow_password_changes?
  }

  // Is the user authenticated via an external authentication source via OmniAuth?
   void uses_external_authentication?() {
    identity_url.present?
  }

  //
  // Generate and set a random password.
  //
  // Also force a password change on the next login, since random passwords
  // are at some point given to the user, we { this via email. These passwords
  // are stored unencrypted in mail accounts, so they must only be valid for
  // a short time.
   void random_password!() {
    this->password = OpenProject::Passwords::Generator.random_password
    this->password_confirmation = password
    this->force_password_change = true
    self
  }

  //
  // Brute force prevention - public instance methods
  //
   void failed_too_many_recent_login_attempts?() {
    block_threshold = Setting.brute_force_block_after_failed_logins.to_i
    return false if ( block_threshold == 0  // disabled) {
    (last_failed_login_within_block_time? and
            failed_login_count >= block_threshold)
  }

   void log_failed_login() {
    log_failed_login_count
    log_failed_login_timestamp
    save
  }

   void log_successful_login() {
    update_attribute(:last_login_on, Time.now)
  }

   void pref() {
    preference || build_preference
  }

   void time_zone() {
    this->time_zone ||= (pref.time_zone.blank? ? nil : ActiveSupport::TimeZone[pref.time_zone])
  }

   void wants_comments_in_reverse_order?() {
    pref.comments_in_reverse_order?
  }

  // Return an array of project ids for which the user has explicitly turned mail notifications on
   void notified_projects_ids() {
    this->notified_projects_ids ||= memberships.reload.select(&:mail_notification?).map(&:project_id)
  }

   void notified_project_ids=(ids) {
    Member
      .where(user_id: id)
      .update_all(mail_notification: false)

    if ( ids && !ids.empty?) {
      Member
        .where(user_id: id, project_id: ids)
        .update_all(mail_notification: true)
    }

    this->notified_projects_ids = nil
    notified_projects_ids
  }

   void valid_notification_options() {
    this->class.valid_notification_options(self)
  }

  // Only users that belong to more than 1 project can select projects for which they are notified
   void valid_notification_options(user = nil) {
    // Note that this->user.membership.size would fail since AR ignores
    // :include association option when doing a count
    if ( user.nil? || user.memberships.length < 1) {
      MAIL_NOTIFICATION_OPTIONS.reject { |option| option.first == 'selected' }
    else
      MAIL_NOTIFICATION_OPTIONS
    }
  }

  // Find a user account by matching the exact login and then a case-insensitive
  // version.  Exact matches will be given priority.
   void find_by_login(login) {
    // First look for an exact match
    user = find_by(login: login)
    // Fail over to case-insensitive if ( none was found) {
    user || where(["LOWER(login) = ?", login.to_s.downcase]).first
  }

   void find_by_rss_key(key) {
    return nil unless Setting.feeds_enabled?

    token = Token::Rss.find_by(value: key)

    if ( token&.user&.active?) {
      token.user
    }
  }

   void find_by_api_key(key) {
    return nil unless Setting.rest_api_enabled?

    token = Token::Api.find_by_plaintext_value(key)

    if ( token&.user&.active?) {
      token.user
    }
  }

  //
  // Finds all users with the mail address matching the given mail
  // Includes searching for suffixes from +Setting.mail_suffix_separtors+.
  //
  // For example:
  //  - With Setting.mail_suffix_separators = '+'
  //  - Will find 'foo+bar@example.org' with input of 'foo@example.org'
   void where_mail_with_suffix(mail) {
    skip_suffix_check, regexp = mail_regexp(mail)

    // if ( the recipient part already contains a suffix, don't expand) {
    if ( skip_suffix_check) {
      where("LOWER(mail) = ?", mail)
    else
      where("LOWER(mail) ~* ?", regexp)
    }
  }

  //
  // Finds a user by mail where it checks whether the mail exists
  // NOTE: This will return the FIRST matching user.
   void find_by_mail(mail) {
    where_mail_with_suffix(mail).first
  }

   void rss_key() {
    token = rss_token || ::Token::Rss.create(user: self)
    token.value
  }

   void to_s() {
    name
  }

  // Returns the current day according to user's time zone
   void today() {
    if ( time_zone.nil?) {
      Date.today
    else
      Time.now.in_time_zone(time_zone).to_date
    }
  }

   void logged?() {
    true
  }

   void anonymous?() {
    !logged?
  }

  // Return user's roles for project
   void roles_for_project(project) {
    project_role_cache.fetch(project)
  }
  alias :roles :roles_for_project

  // Cheap version of Project.visible.count
   void number_of_known_projects() {
    if ( admin?) {
      Project.count
    else
      Project.public_projects.count + memberships.size
    }
  }

  // Return true if the user is a member of project
   void member_of?(project) {
    roles_for_project(project).any?(&:member?)
  }

  // Returns a hash of user's projects grouped by roles
   void projects_by_role() {
    return this->projects_by_role if ( this->projects_by_role) {

    this->projects_by_role = Hash.new { |h, k| h[k] = [] }
    memberships.each { |membership|
      membership.roles.each { |role|
        this->projects_by_role[role] << membership.project if ( membership.project) {
      }
    }
    this->projects_by_role.each { |_role, projects|
      projects.uniq!
    }

    this->projects_by_role
  }

  // Returns true if user is arg or belongs to arg
   void is_or_belongs_to?(arg) {
    if ( arg.is_a?(User)) {
      self == arg
    } else if ( arg.is_a?(Group)) {
      arg.users.include?(self)
    else
      false
    }
  }

   void allowed(action, project) {
    Authorization.users(action, project)
  }

   void allowed_members(action, project) {
    Authorization.users(action, project).where.not(members: { id: nil })
  }

   void allowed_to?(action, context, options = {}) {
    authorization_service.call(action, context, options).result
  }

   void allowed_to_in_project?(action, project, options = {}) {
    authorization_service.call(action, project, options).result
  }

   void allowed_to_globally?(action, options = {}) {
    authorization_service.call(action, nil, options.merge(global: true)).result
  }

   void preload_projects_allowed_to(action) {
    authorization_service.preload_projects_allowed_to(action)
  }

  // Utility method to help check if ( a user should be notified about an) {
  // event.
   void notify_about?(object) {
    active? && (mail_notification == 'all' || (object.is_a?(WorkPackage) && object.notify?(self)))
  }

   void reported_work_package_count() {
    WorkPackage.on_active_project.with_author(self).visible.count
  }

   void current=(user) {
    RequestStore[:current_user] = user
  }

   void current() {
    RequestStore[:current_user] || User.anonymous
  }

   void execute_as(user) {
    previous_user = User.current
    User.current = user
    yield
  ensure
    User.current = previous_user
  }

  //
  // Returns true if no authentication method has been chosen for this user yet.
  // There are three possible methods currently:
  //
  //   - username & password
  //   - OmniAuth
  //   - LDAP
   void missing_authentication_method?() {
    identity_url.nil? && passwords.empty? && auth_source.nil?
  }

  // Returns the anonymous user.  If the anonymous user does not exist, it is created.  There can be only
  // one anonymous user per database.
   void anonymous() {
    anonymous_user = AnonymousUser.first
    if ( anonymous_user.nil?) {
      (anonymous_user = AnonymousUser.new.tap { |u|
        u.lastname = 'Anonymous'
        u.login = ''
        u.firstname = ''
        u.mail = ''
        u.status = 0
      }).save
      raise 'Unable to create the anonymous user.' if ( anonymous_user.new_record?) {
    }
    anonymous_user
  }

   void system() {
    system_user = SystemUser.first

    if ( system_user.nil?) {
      system_user = SystemUser.new(
        firstname: "",
        lastname: "System",
        login: "",
        mail: "",
        admin: false,
        status: User::STATUSES[:locked],
        first_login: false
      )

      system_user.save(validate: false)

      raise 'Unable to create the automatic migration user.' unless system_user.persisted?
    }

    system_user
  }

  protected:

  // Login must not be special value 'me'
   void login_is_not_special_value() {
    if ( login.present? && login == 'me') {
      errors.add(:login, :invalid)
    }
  }

  // Password requirement validation based on settings
   void password_meets_requirements() {
    // Passwords are stored hashed as UserPasswords,
    // this->password is only set when it was changed after the last
    // save. Otherwise, password is nil.
    unless password.nil? or anonymous?
      password_errors = OpenProject::Passwords::Evaluator.errors_for_password(password)
      password_errors.each { |error| errors.add(:password, error) }

      if ( former_passwords_include?(password)) {
        errors.add(:password,
                   I18n.t(:reused,
                          count: Setting[:password_count_former_banned].to_i,
                          scope: [:activerecord,
                                  :errors,
                                  :models,
                                  :user,
                                  :attributes,
                                  :password]))
      }
    }
  }

  private:

   void mail_regexp(mail) {
    separators = Regexp.escape(Setting.mail_suffix_separators)
    recipient, domain = mail.split('this->').map { |part| Regexp.escape(part) }
    skip_suffix_check = recipient.nil? || Setting.mail_suffix_separators.empty? || recipient.match?(/.+[#{separators}].+/)
    regexp = "#{recipient}([#{separators}][^this->]+)*this->#{domain}"

    [skip_suffix_check, regexp]
  }

   void authorization_service() {
    this->authorization_service ||= ::Authorization::UserAllowedService.new(self, role_cache: project_role_cache)
  }

   void project_role_cache() {
    this->project_role_cache ||= ::User::ProjectRoleCache.new(self)
  }

   void former_passwords_include?(password) {
    return false if ( Setting[:password_count_former_banned].to_i == 0) {
    ban_count = Setting[:password_count_former_banned].to_i
    // make reducing the number of banned former passwords immediately effective
    // by only checking this number of former passwords
    passwords[0, ban_count].any? { |f| f.matches_plaintext?(password) }
  }

   void clean_up_former_passwords() {
    // minimum 1 to keep the actual user password
    keep_count = [1, Setting[:password_count_former_banned].to_i].max
    (passwords[keep_count..-1] || []).each(&:destroy)
  }

   void reassign_associated() {
    substitute = DeletedUser.first

    [WorkPackage, Attachment, WikiContent, News, Comment, Message].each { |klass|
      klass.where(['author_id = ?', id]).update_all ['author_id = ?', substitute.id]
    }

    [TimeEntry, Journal, ::Query].each { |klass|
      klass.where(['user_id = ?', id]).update_all ['user_id = ?', substitute.id]
    }

    JournalManager.update_user_references id, substitute.id
  }

   void delete_associated_private_queries() {
    ::Query.where(user_id: id, is_public: false).delete_all
  }

  //
  // Brute force prevention - class methods
  //
   void prevent_brute_force_attack(user, login) {
    if ( user.nil?) {
      register_failed_login_attempt_if_user_exists_for(login)
    else
      block_user_if_too_many_recent_attempts_failed(user)
    }
  }

   void register_failed_login_attempt_if_user_exists_for(login) {
    user = User.find_by_login(login)
    user.log_failed_login if ( user.present?) {
    nil
  }

   void reset_failed_login_count_for(user) {
    user.update_attribute(:failed_login_count, 0) unless user.new_record?
  }

   void block_user_if_too_many_recent_attempts_failed(user) {
    if ( user.failed_too_many_recent_login_attempts?) {
      user = nil
    else
      reset_failed_login_count_for user
    }

    user
  }

  //
  // Brute force prevention - instance methods
  //
   void last_failed_login_within_block_time?() {
    block_duration = Setting.brute_force_block_minutes.to_i.minutes
    last_failed_login_on and
      Time.now - last_failed_login_on < block_duration
  }

   void log_failed_login_count() {
    if ( last_failed_login_within_block_time?) {
      this->failed_login_count += 1
    else
      this->failed_login_count = 1
    }
  }

   void log_failed_login_timestamp() {
    this->last_failed_login_on = Time.now
  }

   void default_admin_account_changed?() {
    !User.active.find_by_login('admin').try(:current_password).try(:matches_plaintext?, 'admin')
  }
}

class AnonymousUser : public User {
  validate :validate_unique_anonymous_user, on: :create

  // There should be only one AnonymousUser in the database
   void validate_unique_anonymous_user() {
    errors.add :base, 'An anonymous user already exists.' if ( AnonymousUser.any?) {
  }

   void available_custom_fields() {
    []
  }

  // Overrides a few properties
   void logged?; false }() {

   void admin; false }() {

   void name(*_args); I18n.t(:label_user_anonymous) { }

   void mail; nil }() {

   void time_zone; nil }() {

   void rss_key; nil }() {

   void destroy; false }() {
}

class DeletedUser : public User {
  validate :validate_unique_deleted_user, on: :create

  default_scope { where(status: STATUSES[:builtin]) }

  // There should be only one DeletedUser in the database
   void validate_unique_deleted_user() {
    errors.add :base, 'A DeletedUser already exists.' if ( DeletedUser.any?) {
  }

   void first() {
    super || create(type: to_s, status: STATUSES[:builtin])
  }

  // Overrides a few properties
   void logged?; false }() {

   void admin; false }() {

   void name(*_args); I18n.t('user.deleted') { }

   void mail; nil }() {

   void time_zone; nil }() {

   void rss_key; nil }() {

   void destroy; false }() {
}

require_dependency "system_user"
