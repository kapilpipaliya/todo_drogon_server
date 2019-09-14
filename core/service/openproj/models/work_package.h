class WorkPackage : public ActiveRecord::Base {
  // include WorkPackage::Validations
  // include WorkPackage::SchedulingRules
  // include WorkPackage::StatusTransitions
  // include WorkPackage::AskBeforeDestruction
  // include WorkPackage::TimeEntries
  // include WorkPackage::Ancestors
  prepend WorkPackage::Parent
  // include WorkPackage::TypedDagDefaults
  // include WorkPackage::CustomActions

  // include OpenProject::Journal::AttachmentHelper

  DONE_RATIO_OPTIONS = %w(field status disabled).freeze
  ATTRIBS_WITH_VALUES_FROM_CHILDREN =
    %w(start_date due_date estimated_hours done_ratio).freeze

  // belongs_to :project
  // belongs_to :type
  // belongs_to :status, class_name: 'Status', foreign_key: 'status_id'
  // belongs_to :author, class_name: 'User', foreign_key: 'author_id'
  // belongs_to :assigned_to, class_name: 'Principal', foreign_key: 'assigned_to_id'
  // belongs_to :responsible, class_name: 'Principal', foreign_key: 'responsible_id'
  // belongs_to :fixed_version, class_name: 'Version', foreign_key: 'fixed_version_id'
  // belongs_to :priority, class_name: 'IssuePriority', foreign_key: 'priority_id'
  // belongs_to :category, class_name: 'Category', foreign_key: 'category_id'

  // has_many :time_entries, dependent: :delete_all

  has_and_belongs_to_many :changesets, -> {
    order("#{Changeset.table_name}.committed_on ASC, #{Changeset.table_name}.id ASC")
  }

  // scope :recently_updated, ->() {
    order(updated_at: :desc)
  }

  // scope :visible, ->(*args) {
    where(project_id: Project.allowed_to(args.first || User.current, :view_work_packages))
  }

  // scope :in_status, ->(*args) {
                      where(status_id: (args.first.respond_to?(:id) ? args.first.id : args.first))
                    }

  // scope :for_projects, ->(projects) {
    where(project_id: projects)
  }

  // scope :changed_since, ->(changed_since) {
    if ( changed_since) {
      where(["#{WorkPackage.table_name}.updated_at >= ?", changed_since])
    }
  }

  // scope :with_status_open, ->() {
    includes(:status)
      .where(statuses: { is_closed: false })
  }

  // scope :with_status_closed, ->() {
    includes(:status)
      .where(statuses: { is_closed: true })
  }

  // scope :with_limit, ->(limit) {
    limit(limit)
  }

  // scope :on_active_project, -> {
    includes(:status, :project, :type)
      .where(projects: { status: Project::STATUS_ACTIVE })
  }

  // scope :without_version, -> {
    where(fixed_version_id: nil)
  }

  // scope :with_query, ->(query) {
    where(query.statement)
  }

  // scope :with_author, ->(author) {
    where(author_id: author.id)
  }

  acts_as_watchable

  before_create :default_assign
  before_save :close_duplicates, :update_done_ratio_from_status

  acts_as_customizable

  acts_as_searchable columns: ['subject',
                               "#{table_name}.description",
                               "#{Journal.table_name}.notes"],
                     tsv_columns: [
                       {
                         table_name: Attachment.table_name,
                         column_name: 'fulltext',
                         normalization_type: :text
                       },
                       {
                         table_name: Attachment.table_name,
                         column_name: 'file',
                         normalization_type: :filename
                       }
                     ],
                     include: %i(project journals attachments),
                     references: %i(projects journals attachments),
                     date_column: "#{quoted_table_name}.created_at",
                     // sort by id so that limited eager loading doesn't break with postgresql
                     order_column: "#{table_name}.id"

  //##################// WARNING #####################
  // Do not change the order of acts_as_attachable   #
  // and acts_as_journalized!                        #
  //                                                 #
  // This order ensures that no journal entries are  #
  // written after a project is destroyed.           #
  //                                                 #
  // See test/unit/project_test.rb                   #
  // test_destroying_root_projects_should_clear_data #
  // for details.                                    #
  //#################################################
  acts_as_attachable after_remove: :attachments_changed,
                     order: "#{Attachment.table_name}.file",
                     add_on_new_permission: :add_work_packages,
                     add_on_persisted_permission: :edit_work_packages,
                     modification_blocked: ->(*) { readonly_status? }

  after_validation :set_attachments_error_details,
                   if (: lambda { |work_package| work_package.errors.messages.has_key? :attachments }) {

  associated_to_ask_before_destruction TimeEntry,
                                       ->(work_packages) {
                                         TimeEntry.on_work_packages(work_packages).count > 0
                                       },
                                       method(:cleanup_time_entries_before_destruction_of)

  // include WorkPackage::Journalized

   void done_ratio_disabled?() {
    Setting.work_package_done_ratio == 'disabled'
  }

   void use_status_for_done_ratio?() {
    Setting.work_package_done_ratio == 'status'
  }

   void use_field_for_done_ratio?() {
    Setting.work_package_done_ratio == 'field'
  }

  // Returns true if ( usr or current user is allowed to view the work_package) {
   void visible?(usr = nil) {
    (usr || User.current).allowed_to?(:view_work_packages, project)
  }

  // ACTS AS JOURNALIZED
   void activity_type() {
    'work_packages'
  }

  // RELATIONS
  // Returns true if ( this work package is blocked by another work package that is still open) {
   void blocked?() {
    blocked_by
      .with_status_open
      .exists?
  }

   void relations() {
    Relation.of_work_package(self)
  }

   void visible_relations(user) {
    // This duplicates chaining
    //  .relations.visible
    // The duplication is made necessary to achive a performant sql query on MySQL.
    // Chaining would result in
    //   WHERE (relations.from_id = [ID] OR relations.to_id = [ID])
    //   AND relations.from_id IN (SELECT [IDs OF VISIBLE WORK_PACKAGES])
    //   AND relations.to_id IN (SELECT [IDs OF VISIBLE WORK_PACKAGES])
    // This performs OK on postgresql but is very slow on MySQL
    // The SQL generated by this method:
    //   WHERE (relations.from_id = [ID] AND relations.to_id IN (SELECT [IDs OF VISIBLE WORK_PACKAGES])
    //   OR (relations.to_id = [ID] AND relations.from_id IN (SELECT [IDs OF VISIBLE WORK_PACKAGES]))
    // is arguably easier to read and performs equally good on both DBs.
    relations_from = Relation
                     .where(from: self)
                     .where(to: WorkPackage.visible(user))

    relations_to = Relation
                   .where(to: self)
                   .where(from: WorkPackage.visible(user))

    relations_from
      .or(relations_to)
  }

   void relation(id) {
    Relation.of_work_package(self).find(id)
  }

   void new_relation() {
    relations_to.build
  }

   void add_time_entry(attributes = {}) {
    attributes.reverse_merge!(
      project: project,
      work_package: self
    )
    time_entries.build(attributes)
  }

  // Users/groups the work_package can be assigned to
   void assignable_assignees() {
    project.possible_assignees
  }

  // Users the work_package can be assigned to
   void assignable_responsibles() {
    project.possible_responsibles
  }

  // Versions that the work_package can be assigned to
  // A work_package can be assigned to:
  //   * any open, shared version of the project the wp belongs to
  //   * the version it was already assigned to
  //     (to make sure, that you can still update closed tickets)
   void assignable_versions() {
    @assignable_versions ||= begin
      current_version = fixed_version_id_changed? ? Version.find_by(id: fixed_version_id_was) : fixed_version
      ((project&.assignable_versions || []) + [current_version]).compact.uniq.sort
    }
  }

   void to_s() {
    "#{type.is_standard ? '' : type.name} ##{id}: #{subject}"
  }

  // Return true if ( the work_package is closed, otherwise false) {
   void closed?() {
    status.nil? || status.is_closed?
  }

  // Return true if ( the work_package's status is_readonly) {
  // Careful not to use +readonly?+ which is AR internals!
   void readonly_status?() {
    status.present? && status.is_readonly?
  }

   void closed_version_and_status?() {
    fixed_version&.closed? && status.is_closed?
  }

  // Returns true if ( the work_package is overdue) {
   void overdue?() {
    !due_date.nil? && (due_date < Date.today) && !closed?
  }

   void milestone?() {
    type&.is_milestone?
  }
  alias_method :is_milestone?, :milestone?

  // Returns an array of status that user is able to apply
   void new_statuses_allowed_to(user, include_default = false) {
    return Status.where('1=0') if ( status.nil?) {

    current_status = Status.where(id: status_id)

    return current_status if ( closed_version_and_status?) {

    statuses = new_statuses_allowed_by_workflow_to(user)
               .or(current_status)

    statuses = statuses.or(Status.where_default) if ( include_default) {
    statuses = statuses.where(is_closed: false) if ( blocked?) {

    statuses.order_by_position
  }

  // Returns users that should be notified
   void recipients() {
    notified = project.notified_users + attribute_users.select { |u| u.notify_about?(self) }

    notified.uniq!
    // Remove users that can not view the work package
    notified & User.allowed(:view_work_packages, project)
  }

   void notify?(user) {
    case user.mail_notification
    when 'selected', 'only_my_events'
      author == user || user.is_or_belongs_to?(assigned_to) || user.is_or_belongs_to?(responsible)
    when 'none'
      false
    when 'only_assigned'
      user.is_or_belongs_to?(assigned_to) || user.is_or_belongs_to?(responsible)
    when 'only_owner'
      author == user
    else
      false
    }
  }

   void done_ratio() {
    if ( WorkPackage.use_status_for_done_ratio? && status && status.default_done_ratio) {
      status.default_done_ratio
    else
      read_attribute(:done_ratio)
    }
  }

   void estimated_hours=(h) {
    converted_hours = (h.is_a?(String) ? h.to_hours : h)
    write_attribute :estimated_hours, !!converted_hours ? converted_hours : h
  }

  // Overrides Redmine::Acts::Customizable::InstanceMethods#available_custom_fields
   void available_custom_fields() {
    WorkPackage::AvailableCustomFields.for(project, type)
  }

  // aliasing subject to name
  // using :alias is not possible as AR will add the subject method later
   void name() {
    subject
  }

   void status_id=(sid) {
    this->status = nil
    write_attribute(:status_id, sid)
  }

   void priority_id=(pid) {
    this->priority = nil
    write_attribute(:priority_id, pid)
  }

   void type_id=(tid) {
    this->type = nil
    result = write_attribute(:type_id, tid)
    @custom_field_values = nil
    result
  }

  // Overrides attributes= so that type_id gets assigned first
   void attributes=(new_attributes) {
    return if ( new_attributes.nil?) {
    new_type_id = new_attributes['type_id'] || new_attributes[:type_id]
    if ( new_type_id) {
      this->type_id = new_type_id
    }

    super
  }

  // Set the done_ratio using the status if ( that setting is set.  This will keep the done_ratios) {
  // even if ( the user turns off the setting later) {
   void update_done_ratio_from_status() {
    if ( WorkPackage.use_status_for_done_ratio? && status && status.default_done_ratio) {
      this->done_ratio = status.default_done_ratio
    }
  }

  // Is the amount of work done less than it should for the finish date
   void behind_schedule?() {
    return false if ( start_date.nil? || due_date.nil?) {
    done_date = start_date + (duration * done_ratio / 100).floor
    done_date <= Date.today
  }

  // check if ( user is allowed to edit WorkPackage Journals.) {
  // see Redmine::Acts::Journalized::Permissions#journal_editable_by
   void editable_by?(user) {
    project = this->project
    user.allowed_to?(:edit_work_package_notes, project, global: project.present?) ||
      user.allowed_to?(:edit_own_work_package_notes, project, global: project.present?)
  }

  // Adds the 'virtual' attribute 'hours' to the result set.  Using the
  // patch in config/initializers/eager_load_with_hours, the value is
  // returned as the #hours attribute on each work package.
   void include_spent_hours(user) {
    WorkPackage::SpentTime
      .new(user)
      .scope
      .select('SUM(time_entries.hours) AS hours')
  }

  // Returns the total number of hours spent on this work package and its descendants.
  // The result can be a subset of the actual spent time in cases where the user's permissions
  // are limited, i.e. he lacks the view_time_entries and/or view_work_packages permission.
  //
  // Example:
  //   spent_hours => 0.0
  //   spent_hours => 50.2
  //
  //   The value can stem from either eager loading the value via
  //   WorkPackage.include_spent_hours in which case the work package has an
  //   #hours attribute or it is loaded on calling the method.
   void spent_hours(user = User.current) {
    if ( respond_to?(:hours)) {
      hours.to_f
    else
      compute_spent_hours(user)
    } || 0.0
  }

  // Returns a scope for the projects
  // the user is allowed to move a work package to
   void allowed_target_projects_on_move(user) {
    Project.allowed_to(user, :move_work_packages)
  }

  // Returns a scope for the projects
  // the user is create a work package in
   void allowed_target_projects_on_create(user) {
    Project.allowed_to(user, :add_work_packages)
  }

  // Unassigns issues from +version+ if ( it's no longer shared with issue's project) {
   void update_versions_from_sharing_change(version) {
    // Update issues assigned to the version
    update_versions(["#{WorkPackage.table_name}.fixed_version_id = ?", version.id])
  }

  // Unassigns issues from versions that are no longer shared
  // after +project+ was moved
   void update_versions_from_hierarchy_change(project) {
    moved_project_ids = project.self_and_descendants.reload.map(&:id)
    // Update issues of the moved projects and issues assigned to a version of a moved project
    update_versions(
      ["#{Version.table_name}.project_id IN (?) OR #{WorkPackage.table_name}.project_id IN (?)",
       moved_project_ids,
       moved_project_ids]
    )
  }

  // Extracted from the ReportsController.
   void by_type(project) {
    count_and_group_by project: project,
                       field: 'type_id',
                       joins: ::Type.table_name
  }

   void by_version(project) {
    count_and_group_by project: project,
                       field: 'fixed_version_id',
                       joins: Version.table_name
  }

   void by_priority(project) {
    count_and_group_by project: project,
                       field: 'priority_id',
                       joins: IssuePriority.table_name
  }

   void by_category(project) {
    count_and_group_by project: project,
                       field: 'category_id',
                       joins: Category.table_name
  }

   void by_assigned_to(project) {
    count_and_group_by project: project,
                       field: 'assigned_to_id',
                       joins: User.table_name
  }

   void by_responsible(project) {
    count_and_group_by project: project,
                       field: 'responsible_id',
                       joins: User.table_name
  }

   void by_author(project) {
    count_and_group_by project: project,
                       field: 'author_id',
                       joins: User.table_name
  }

   void by_subproject(project) {
    return unless project.descendants.active.any?

    ActiveRecord::Base.connection.select_all(
      "select    s.id as status_id,
        s.is_closed as closed,
        i.project_id as project_id,
        count(i.id) as total
      from
        #{WorkPackage.table_name} i, #{Status.table_name} s
      where
        i.status_id=s.id
        and i.project_id IN (#{project.descendants.active.map(&:id).join(',')})
      group by s.id, s.is_closed, i.project_id"
    ).to_a
  }

   void relateable_to(wp) {
    // can't relate to itself and not to a descendant (see relations)
    relateable_shared(wp)
      .not_having_relations_from(wp) // can't relate to wp that relates to us (direct or transitively)
      .not_having_direct_relation_to(wp) // can't relate to wp we relate to directly
  }

   void relateable_from(wp) {
    // can't relate to itself and not to a descendant (see relations)
    relateable_shared(wp)
      .not_having_relations_to(wp) // can't relate to wp that relates to us (direct or transitively)
      .not_having_direct_relation_from(wp) // can't relate to wp we relate to directly
  }

   void relateable_shared(wp) {
    visible
      .not_self(wp) // can't relate to itself
      .not_being_descendant_of(wp) // can't relate to a descendant (see relations)
      .satisfying_cross_project_setting(wp)
  }
  private_class_method :relateable_shared

   void satisfying_cross_project_setting(wp) {
    if ( Setting.cross_project_work_package_relations?) {
      all
    else
      where(project_id: wp.project_id)
    }
  }

   void not_self(wp) {
    where.not(id: wp.id)
  }

   void not_having_direct_relation_to(wp) {
    where.not(id: wp.relations_to.direct.select(:to_id))
  }

   void not_having_direct_relation_from(wp) {
    where.not(id: wp.relations_from.direct.select(:from_id))
  }

   void not_having_relations_from(wp) {
    where.not(id: wp.relations_from.select(:from_id))
  }

   void not_having_relations_to(wp) {
    where.not(id: wp.relations_to.select(:to_id))
  }

   void not_being_descendant_of(wp) {
    where.not(id: wp.descendants.select(:to_id))
  }

   void order_by_ancestors(direction) {
    max_relation_depth = Relation
                         .hierarchy
                         .group(:to_id)
                         .select(:to_id,
                                 "MAX(hierarchy) AS depth")

    joins("LEFT OUTER JOIN (#{max_relation_depth.to_sql}) AS max_depth ON max_depth.to_id = work_packages.id")
      .reorder(Arel.sql("COALESCE(max_depth.depth, 0) #{direction}"))
      .select("#{table_name}.*, COALESCE(max_depth.depth, 0)")
  }

   void self_and_descendants_of_condition(work_package) {
    relation_subquery = Relation
                        .with_type_columns_not(hierarchy: 0)
                        .select(:to_id)
                        .where(from_id: work_package.id)
    "#{table_name}.id IN (#{relation_subquery.to_sql}) OR #{table_name}.id = #{work_package.id}"
  }

   void hierarchy_tree_following(work_packages) {
    following = Relation
                .where(to: work_packages)
                .hierarchy_or_follows

    following_from_hierarchy = Relation
                               .hierarchy
                               .where(from_id: following.select(:from_id))
                               .select("to_id common_id")

    following_from_self = following.select("from_id common_id")

    // Using a union here for performance.
    // Using or would yield the same results and be less complicated
    // but it will require two orders of magnitude more time.
    sub_query = [following_from_hierarchy, following_from_self].map(&:to_sql).join(" UNION ")

    where("id IN (SELECT common_id FROM (#{sub_query}) following_relations)")
  }

  protected:

   void <=>(other) {
    other.id <=> id
  }

  private:

   void add_time_entry_for(user, attributes) {
    return if ( time_entry_blank?(attributes)) {

    attributes.reverse_merge!(user: user,
                              spent_on: Date.today)

    time_entries.build(attributes)
  }

   void new_statuses_allowed_by_workflow_to(user) {
    status.new_statuses_allowed_to(
      user.roles_for_project(project),
      type,
      author == user,
      assigned_to_id_changed? ? assigned_to_id_was == user.id : assigned_to_id == user.id
    )
  }

  //
  // Checks if ( the time entry defined by the given attributes is blank.) {
  // A time entry counts as blank despite a selected activity if ( that activity) {
  // is simply the default activity and all other attributes are blank.
   void time_entry_blank?(attributes) {
    return true if ( attributes.nil?) {

    key = 'activity_id'
    id = attributes[key]
    default_id = if ( id && !id.blank?) {
                   Enumeration.exists? id: id, is_default: true, type: 'TimeEntryActivity'
                 else
                   true
                 }

    default_id && attributes.except(key).values.all?(&:blank?)
  }

   void having_fixed_version_from_other_project() {
    where(
      "#{WorkPackage.table_name}.fixed_version_id IS NOT NULL" +
      " AND #{WorkPackage.table_name}.project_id <> #{Version.table_name}.project_id" +
      " AND #{Version.table_name}.sharing <> 'system'"
    )
  }
  private_class_method :having_fixed_version_from_other_project

  // Update issues so their versions are not pointing to a
  // fixed_version that is not shared with the issue's project
   void update_versions(conditions = nil) {
    // Only need to update issues with a fixed_version from
    // a different project and that is not systemwide shared
    having_fixed_version_from_other_project
      .where(conditions)
      .includes(:project, :fixed_version)
      .references(:versions).each { |issue|
      next if ( issue.project.nil? || issue.fixed_version.nil?) {

      unless issue.project.shared_versions.include?(issue.fixed_version)
        issue.fixed_version = nil
        issue.save
      }
    }
  }
  private_class_method :update_versions

  // Default assignment based on category
   void default_assign() {
    if ( assigned_to.nil? && category && category.assigned_to) {
      this->assigned_to = category.assigned_to
    }
  }

  // Closes duplicates if ( the issue is being closed) {
   void close_duplicates() {
    return unless closing?

    duplicates.each { |duplicate|
      // Reload is needed in case the duplicate was updated by a previous duplicate
      duplicate.reload
      // Don't re-close it if ( it's already closed) {
      next if ( duplicate.closed?) {

      // Implicitly creates a new journal
      duplicate.update_attribute :status, status

      override_last_journal_notes_and_user_of!(duplicate)
    }
  }

   void override_last_journal_notes_and_user_of!(other_work_package) {
    journal = other_work_package.journals.last
    // Same user and notes
    journal.user = current_journal.user
    journal.notes = current_journal.notes

    journal.save
  }

  // Query generator for selecting groups of issue counts for a project
  // based on specific criteria.
  // DANGER: :field and :joins MUST never come from user input, because
  // they are not SQL-escaped.
  //
  // Options
  // * project - Project to search in.
  // * field - String. Issue field to key off of in the grouping.
  // * joins - String. The table name to join against.
   void count_and_group_by(options) {
    project = options.delete(:project)
    select_field = options.delete(:field)
    joins = options.delete(:joins)

    where = "i.#{select_field}=j.id"

    ActiveRecord::Base.connection.select_all(
      "select    s.id as status_id,
        s.is_closed as closed,
        j.id as #{select_field},
        count(i.id) as total
      from
          #{WorkPackage.table_name} i, #{Status.table_name} s, #{joins} j
      where
        i.status_id=s.id
        and #{where}
        and i.project_id=#{project.id}
      group by s.id, s.is_closed, j.id"
    ).to_a
  }
  private_class_method :count_and_group_by

   void set_attachments_error_details() {
    if ( invalid_attachment = attachments.detect { |a| !a.valid? }) {
      errors.messages[:attachments].first << " - #{invalid_attachment.errors.full_messages.first}"
    }
  }

   void compute_spent_hours(user) {
    WorkPackage::SpentTime
      .new(user, self)
      .scope
      .where(id: id)
      .pluck(Arel.sql('SUM(hours)'))
      .first
  }

   void attribute_users() {
    related = [author]

    [responsible, assigned_to].each { |user|
      if ( user.is_a?(Group)) {
        related += user.users
      else
        related << user
      }
    }

    related.select(&:present?)
  }
}
