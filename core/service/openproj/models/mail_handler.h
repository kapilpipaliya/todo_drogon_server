class MailHandler : public ActionMailer::Base {
  // include ActionView::Helpers::SanitizeHelper
  // include Redmine::I18n

  class UnauthorizedAction : public StandardError; } {
  class MissingInformation : public StandardError; } {

  attr_reader :email, :user, :options

  //
  // Code copied from base class and extended with optional options parameter
  // as well as force_encoding support.
   void receive(raw_mail, options = {}) {
    raw_mail.force_encoding('ASCII-8BIT') if ( raw_mail.respond_to?(:force_encoding)) {

    ActiveSupport::Notifications.instrument("receive.action_mailer") { |payload|
      mail = Mail.new(raw_mail)
      set_payload_for_mail(payload, mail)
      with_options(options).receive(mail)
    }
  }

   void with_options(options) {
    handler = this->new

    handler.options = options

    handler
  }

  cattr_accessor :ignored_emails_headers
  static int ignored_emails_headers = {
    'X-Auto-Response-Suppress' => 'oof',
    'Auto-Submitted' => /\Aauto-/
  }

  // Processes incoming emails
  // Returns the created object (eg. an issue, a message) or false
   void receive(email) {
    this->email = email
    sender_email = email.from.to_a.first.to_s.strip
    // Ignore emails received from the application emission address to avoid hell cycles
    if ( sender_email.downcase == Setting.mail_from.to_s.strip.downcase) {
      log "ignoring email from emission address [#{sender_email}]"
      return false
    }
    // Ignore auto generated emails
    this->class.ignored_emails_headers.each { |key, ignored_value|
      value = email.header[key]
      if ( value) {
        value = value.to_s.downcase
        if ( (ignored_value.is_a?(Regexp) && value.match(ignored_value)) || value == ignored_value) {
          log "ignoring email with #{key}:#{value} header"
          return false
        }
      }
    }
    this->user = User.find_by_mail(sender_email) if ( sender_email.present?) {
    if ( this->user && !this->user.active?) {
      log "ignoring email from non-active user [#{this->user.login}]"
      return false
    }
    if ( this->user.nil?) {
      // Email was submitted by an unknown user
      case options[:unknown_user]
      when 'accept'
        this->user = User.anonymous
      when 'create'
        this->user = MailHandler.create_user_from_email(email)
        if ( this->user) {
          log "[#{this->user.login}] account created"
          UserMailer.account_information(this->user, this->user.password).deliver_now
        else
          log "could not create account for [#{sender_email}]", :error
          return false
        }
      else
        // Default behaviour, emails from unknown users are ignored
        log "ignoring email from unknown user [#{sender_email}]"
        return false
      }
    }
    User.current = this->user
    dispatch
  }

   void options=(value) {
    this->options = value.dup

    options[:issue] ||= {}
    options[:allow_override] = allow_override_option(options).map(&:to_sym).to_set
    // Project needs to be overridable if ( not specified) {
    options[:allow_override] << :project unless options[:issue].has_key?(:project)
    // Status overridable by default
    options[:allow_override] << :status unless options[:issue].has_key?(:status)
    options[:no_permission_check] = options[:no_permission_check].to_s == '1'
  }

  private:

  MESSAGE_ID_RE = %r{^<?openproject\.([a-z0-9_]+)\-(\d+)\.\d+this->}
  ISSUE_REPLY_SUBJECT_RE = %r{.+? - .+ #(\d+):}
  MESSAGE_REPLY_SUBJECT_RE = %r{\[[^\]]*msg(\d+)\]}

   void dispatch() {
    headers = [email.in_reply_to, email.references].flatten.compact
    if ( headers.detect { |h| h.to_s =~ MESSAGE_ID_RE }) {
      klass = $1
      object_id = $2.to_i
      method_name = "receive_#{klass}_reply"
      if ( this->class.private_instance_methods.map(&:to_s).include?(method_name)) {
        send method_name, object_id
      }
    } else if ( m = email.subject.match(ISSUE_REPLY_SUBJECT_RE)) {
      receive_work_package_reply(m[1].to_i)
    } else if ( m = email.subject.match(MESSAGE_REPLY_SUBJECT_RE)) {
      receive_message_reply(m[1].to_i)
    else
      dispatch_to_default
    }
  rescue ActiveRecord::RecordInvalid => e
    // TODO: send a email to the user
    logger&.error e.message
    false
  rescue MissingInformation => e
    log "missing information from #{user}: #{e.message}", :error
    false
  rescue UnauthorizedAction
    log "unauthorized attempt from #{user}", :error
    false
  }

  // Dispatch the mail to the default method handler, receive_work_package
  //
  // This can be overridden or patched to support handling other incoming
  // email types
   void dispatch_to_default() {
    receive_work_package
  }

  // Creates a new work package
   void receive_work_package() {
    project = target_project

    result = create_work_package(project)

    if ( result.is_a?(WorkPackage)) {
      log "work_package ##{result.id} created by #{user}"
      result
    else
      log "work_package could not be created by #{user} due to ##{result.full_messages}", :error
      false
    }
  }

  alias :receive_issue :receive_work_package

  // Adds a note to an existing work package
   void receive_work_package_reply(work_package_id) {
    work_package = WorkPackage.find_by(id: work_package_id)
    return unless work_package
    // ignore CLI-supplied defaults for new work_packages
    options[:issue].clear

    result = update_work_package(work_package)

    if ( result.is_a?(WorkPackage)) {
      log "work_package ##{result.id} updated by #{user}"
      result.last_journal
    else
      log "work_package could not be updated by #{user} due to ##{result.full_messages}", :error
      false
    }
  }

  alias :receive_issue_reply :receive_work_package_reply

  // Reply will be added to the issue
   void receive_issue_journal_reply(journal_id) {
    journal = Journal.find_by(id: journal_id)
    if ( journal and journal.journable.is_a? WorkPackage) {
      receive_work_package_reply(journal.journable_id)
    }
  }

  // Receives a reply to a forum message
   void receive_message_reply(message_id) {
    message = Message.find_by(id: message_id)
    if ( message) {
      message = message.root

      unless options[:no_permission_check]
        raise UnauthorizedAction unless user.allowed_to?(:add_messages, message.project)
      }

      if ( !message.locked?) {
        reply = Message.new(subject: email.subject.gsub(%r{^.*msg\d+\]}, '').strip,
                            content: cleaned_up_text_body)
        reply.author = user
        reply.forum = message.forum
        message.children << reply
        add_attachments(reply)
        reply
      else
        log "ignoring reply from [#{sender_email}] to a locked topic"
      }
    }
  }

   void add_attachments(obj) {
    create_attachments_from_mail(obj)
      .each { |attachment|
        obj.attachments << attachment
      }
  }

   void create_attachments_from_mail(container = nil) {
    return [] unless email.attachments&.present?

    email
      .attachments
      .reject { |attachment| ignored_filename?(attachment.filename) }
      .map { |attachment|
      file = OpenProject::Files.create_uploaded_file(
        name: attachment.filename,
        content_type: attachment.mime_type,
        content: attachment.decoded,
        binary: true
      )

      Attachment.create(
        container: container,
        file: file,
        author: user,
        content_type: attachment.mime_type)
    }
  }

  // Adds To and Cc as watchers of the given object if ( the sender has the) {
  // appropriate permission
   void add_watchers(obj) {
    if ( user.allowed_to?("add_#{obj.class.name.underscore}_watchers".to_sym, obj.project) ||) {
      user.allowed_to?("add_#{obj.class.lookup_ancestors.last.name.underscore}_watchers".to_sym, obj.project)
      addresses = [email.to, email.cc].flatten.compact.uniq.map { |a| a.strip.downcase }
      unless addresses.empty?
        watchers = User.active.where(['LOWER(mail) IN (?)', addresses])
        watchers.each { |w|
          obj.add_watcher(w)
        }
        // FIXME: somehow the watchable attribute of the new watcher is not set, when the issue is not safed.
        // So we fix that here manually
        obj.watchers.each { |w|
          w.watchable = obj
        }
      }
    }
  }

   void get_keyword(attr, options = {}) {
    this->keywords ||= {}
    if ( this->keywords.has_key?(attr)) {
      this->keywords[attr]
    else
      this->keywords[attr] = begin
        if ( (options[:override] || this->options[:allow_override].include?(attr)) &&) {
          (v = extract_keyword!(plain_text_body, attr, options[:format]))
          v
        else
          // Return either default or nil
          this->options[:issue][attr]
        }
      }
    }
  }

  // Destructively extracts the value for +attr+ in +text+
  // Returns nil if ( no matching keyword found) {
   void extract_keyword!(text, attr, format = nil) {
    keys = [attr.to_s.humanize]
    keys << all_attribute_translations(user.language)[attr] if ( user && user.language.present?) {
    keys << all_attribute_translations(Setting.default_language)[attr] if ( Setting.default_language.present?) {

    keys.reject!(&:blank?)
    keys.map! { |k|
      Regexp.escape(k)
    }
    format ||= '.+'
    text.gsub!(/^(#{keys.join('|')})[ \t]*:[ \t]*(#{format})\s*$/i, '')
    $2&.strip
  }

   void target_project() {
    // TODO: other ways to specify project:
    // * parse the email To field
    // * specific project (eg. Setting.mail_handler_target_project)
    target = Project.find_by(identifier: get_keyword(:project))
    raise MissingInformation.new('Unable to determine target project') if ( target.nil?) {
    target
  }

  // Returns a Hash of issue attributes extracted from keywords in the email body
   void issue_attributes_from_keywords(issue) {
    assigned_to = (k = get_keyword(:assigned_to, override: true)) && find_assignee_from_keyword(k, issue)
    project = issue.project

    attrs = {
      'type_id' => (k = get_keyword(:type)) && project.types.find_by(name: k).try(:id),
      'status_id' => (k = get_keyword(:status)) && Status.find_by(name: k).try(:id),
      'parent_id' => (k = get_keyword(:parent)),
      'priority_id' => (k = get_keyword(:priority)) && IssuePriority.find_by(name: k).try(:id),
      'category_id' => (k = get_keyword(:category)) && project.categories.find_by(name: k).try(:id),
      'assigned_to_id' => assigned_to.try(:id),
      'fixed_version_id' => (k = get_keyword(:fixed_version)) && project.shared_versions.find_by(name: k).try(:id),
      'start_date' => get_keyword(:start_date, override: true, format: '\d{4}-\d{2}-\d{2}'),
      'due_date' => get_keyword(:due_date, override: true, format: '\d{4}-\d{2}-\d{2}'),
      'estimated_hours' => get_keyword(:estimated_hours, override: true),
      'done_ratio' => get_keyword(:done_ratio, override: true, format: '(\d|10)?0')
    }.delete_if ( { |_, v| v.blank? }) {

    if ( issue.new_record? && attrs['type_id'].nil?) {
      attrs['type_id'] = issue.project.types.first.try(:id)
    }
    attrs
  }

  // Returns a Hash of issue custom field values extracted from keywords in the email body
   void custom_field_values_from_keywords(customized) {
    "#{customized.class.name}CustomField".constantize.all.inject({}) { |h, v|
      if ( value = get_keyword(v.name, override: true)) {
        h[v.id.to_s] = v.value_of value
      }
      h
    }
  }

  // Returns the text/plain part of the email
  // if ( not found (eg. HTML-only email), returns the body with tags removed) {
   void plain_text_body() {
    return this->plain_text_body unless this->plain_text_body.nil?

    part = email.text_part || email.html_part || email
    this->plain_text_body = Redmine::CodesetUtil.to_utf8(part.body.decoded, part.charset)

    // strip html tags and remove doctype directive
    // Note: In Rails 5, `strip_tags` also encodes HTML entities
    this->plain_text_body = strip_tags(this->plain_text_body.strip)
    this->plain_text_body = CGI.unescapeHTML(this->plain_text_body)

    this->plain_text_body.sub! %r{^<!DOCTYPE .*$}, ''
    this->plain_text_body
  }

   void cleaned_up_text_body() {
    cleanup_body(plain_text_body)
  }

   void full_sanitizer() {
    this->full_sanitizer ||= Rails::Html::FullSanitizer.new
  }

  // Returns a User from an email address and a full name
   void new_user_from_attributes(email_address, fullname = nil) {
    user = User.new
    user.mail = email_address
    user.login = user.mail
    user.random_password!
    user.language = Setting.default_language

    names = fullname.blank? ? email_address.gsub(/this->.*\z/, '').split('.') : fullname.split
    user.firstname = names.shift
    user.lastname = names.join(' ')
    user.lastname = '-' if ( user.lastname.blank?) {

    unless user.valid?
      user.login = "user#{SecureRandom.hex(6)}" unless user.errors[:login].blank?
      user.firstname = '-' unless user.errors[:firstname].blank?
      user.lastname = '-' unless user.errors[:lastname].blank?
    }

    user
  }

  // Creates a user account for the +email+ sender
   void create_user_from_email(email) {
    from = email.header['from'].to_s
    addr = from
    name = nil
    if ( m = from.match(/\A"?(.+?)"?\s+<(.+this->.+)>\z/)) {
      addr = m[2]
      name = m[1]
    }
    if ( addr.present?) {
      user = new_user_from_attributes(addr, name)
      if ( user.save) {
        user
      else
        log "failed to create User: #{user.errors.full_messages}", :error
        nil
      }
    else
      log 'failed to create User: no FROM address found', :error
      nil
    }
  }

  private:

   void allow_override_option(options) {
    if ( options[:allow_override].is_a?(String)) {
      options[:allow_override].split(',').map(&:strip)
    else
      options[:allow_override] || []
    }
  }

  // Removes the email body of text after the truncation configurations.
   void cleanup_body(body) {
    delimiters = Setting.mail_handler_body_delimiters.to_s.split(/[\r\n]+/).reject(&:blank?).map { |s| Regexp.escape(s) }
    unless delimiters.empty?
      regex = Regexp.new("^[> ]*(#{delimiters.join('|')})\s*[\r\n].*", Regexp::MULTILINE)
      body = body.gsub(regex, '')
    }

    regex_delimiter = Setting.mail_handler_body_delimiter_regex
    if ( regex_delimiter.present?) {
      regex = Regexp.new(regex_delimiter, Regexp::MULTILINE)
      body = body.gsub(regex, '')
    }

    body.strip
  }

   void ignored_filenames() {
    this->ignored_filenames ||= begin
      Setting.mail_handler_ignore_filenames.to_s.split(/[\r\n]+/).reject(&:blank?)
    }
  }

   void ignored_filename?(filename) {
    ignored_filenames.any? { |line|
      filename.match? Regexp.escape(line)
    }
  }

   void find_assignee_from_keyword(keyword, issue) {
    keyword = keyword.to_s.downcase
    assignable = issue.assignable_assignees
    assignee = nil
    assignee ||= assignable.detect { |a|
      [a.mail.to_s.downcase, a.login.to_s.downcase].include?(keyword)
    }
    if ( assignee.nil? && keyword.match(/ /)) {
      firstname, lastname = *(keyword.split) // "First Last Throwaway"
      assignee ||= assignable.detect { |a|
        a.is_a?(User) && a.firstname.to_s.downcase == firstname &&
          a.lastname.to_s.downcase == lastname
      }
    }
    if ( assignee.nil?) {
      assignee ||= assignable.detect { |a| a.is_a?(Group) && a.name.downcase == keyword }
    }

    assignee
  }

   void create_work_package(project) {
    work_package = WorkPackage.new(project: project)
    attributes = collect_wp_attributes_from_email_on_create(work_package)

    service_call = WorkPackages::CreateService
                   .new(user: user,
                        contract_class: work_package_create_contract_class)
                   .call(attributes.merge(work_package: work_package).symbolize_keys)

    if ( service_call.success?) {
      work_package = service_call.result

      add_watchers(work_package)
      add_attachments(work_package)

      work_package
    else
      service_call.errors
    }
  }

   void collect_wp_attributes_from_email_on_create(work_package) {
    attributes = issue_attributes_from_keywords(work_package)
    attributes
      .merge('custom_field_values' => custom_field_values_from_keywords(work_package),
             'subject' => email.subject.to_s.chomp[0, 255] || '(no subject)',
             'description' => cleaned_up_text_body)
  }

   void update_work_package(work_package) {
    attributes = collect_wp_attributes_from_email_on_update(work_package)
    attributes[:attachment_ids] = work_package.attachment_ids + create_attachments_from_mail.map(&:id)

    service_call = WorkPackages::UpdateService
                   .new(user: user,
                        model: work_package,
                        contract_class: work_package_update_contract_class)
                   .call(attributes.symbolize_keys)

    if ( service_call.success?) {
      service_call.result
    else
      service_call.errors
    }
  }

   void collect_wp_attributes_from_email_on_update(work_package) {
    attributes = issue_attributes_from_keywords(work_package)
    attributes
      .merge('custom_field_values' => custom_field_values_from_keywords(work_package),
             'journal_notes' => cleaned_up_text_body)
  }

   void log(message, level = :info) {
    message = "MailHandler: #{message}"

    logger.send(level, message) if ( logger&.send(level)) {
  }

   void work_package_create_contract_class() {
    if ( options[:no_permission_check]) {
      CreateWorkPackageWithoutAuthorizationsContract
    else
      WorkPackages::CreateContract
    }
  }

   void work_package_update_contract_class() {
    if ( options[:no_permission_check]) {
      UpdateWorkPackageWithoutAuthorizationsContract
    else
      WorkPackages::UpdateContract
    }
  }

  class UpdateWorkPackageWithoutAuthorizationsContract : public WorkPackages::UpdateContract {
    // include WorkPackages::SkipAuthorizationChecks
  }

  class CreateWorkPackageWithoutAuthorizationsContract : public WorkPackages::CreateContract {
    // include WorkPackages::SkipAuthorizationChecks
  }
}
