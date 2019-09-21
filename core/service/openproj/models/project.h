#pragma once
#include "activerecord.h"
namespace openproj {
namespace models {
class Project : public ActiveRecord::Base {
  // extend Pagination::Model
  // extend FriendlyId

  // include Project::Copy
  // include Project::Storage
  // include Project::Activity

  // Project statuses
//  STATUS_ACTIVE     = 1
//  STATUS_ARCHIVED   = 9

//  enum status: { active: STATUS_ACTIVE, archived: STATUS_ARCHIVED }

//  // Maximum length for project identifiers
//  IDENTIFIER_MAX_LENGTH = 100

//  // reserved identifiers
//  RESERVED_IDENTIFIERS = %w(new).freeze

//  // Specific overridden Activities
//  // has_many :time_entry_activities
//  // has_many :members, -> {
//    includes(:principal, :roles)
//      .where(
//        "#{Principal.table_name}.type="User" AND (
//          #{User.table_name}.status=#{Principal::STATUSES[:active]} OR
//          #{User.table_name}.status=#{Principal::STATUSES[:invited]}
//        )"
//      )
//      .references(:principal, :roles)
//  }

  // has_many :possible_assignee_members, -> {
//    includes(:principal, :roles)
//      .where(Project.possible_principles_condition)
//      .references(:principals, :roles)
//  }, class_name: "Member"
//  // Read only
//  // has_many :possible_assignees,
//           ->(object) {
//             // Have to reference members and roles again although
//             // possible_assignee_members does already specify it to be able to use the
//             // Project.possible_principles_condition there
//             //
//             // The .where(members_users: { project_id: object.id })
//             // part is an optimization preventing to have all the members joined
//             includes(members: :roles)
//               .where(members_users: { project_id: object.id })
//               .references(:roles)
//               .merge(Principal.order_by_name)
//           },
//           through: :possible_assignee_members,
//           source: :principal
//  // has_many :possible_responsible_members, -> {
//    includes(:principal, :roles)
//      .where(Project.possible_principles_condition)
//      .references(:principals, :roles)
//  }, class_name: "Member"
//  // Read only
//  // has_many :possible_responsibles,
//           ->(object) {
//             // Have to reference members and roles again although
//             // possible_responsible_members does already specify it to be able to use
//             // the Project.possible_principles_condition there
//             //
//             // The .where(members_users: { project_id: object.id })
//             // part is an optimization preventing to have all the members joined
//             includes(members: :roles)
//               .where(members_users: { project_id: object.id })
//               .references(:roles)
//               .merge(Principal.order_by_name)
//           },
//           through: :possible_responsible_members,
//           source: :principal
//  // has_many :memberships, class_name: "Member"
//  // has_many :member_principals,
//           -> {
//             includes(:principal)
//               .references(:principals)
//               .where("#{Principal.table_name}.type="Group" OR " +
//               "(#{Principal.table_name}.type="User" AND " +
//               "(#{Principal.table_name}.status=#{Principal::STATUSES[:active]} OR " +
//               "#{Principal.table_name}.status=#{Principal::STATUSES[:registered]} OR " +
//               "#{Principal.table_name}.status=#{Principal::STATUSES[:invited]}))")
//           },
//           class_name: "Member"
//  // has_many :users, through: :members, source: :principal
//  // has_many :principals, through: :member_principals, source: :principal

//  // has_many :enabled_modules, dependent: :delete_all
//  has_and_belongs_to_many :types, -> {
//    order("#{::Type.table_name}.position")
//  }
//  // has_many :work_packages, -> {
//    order("#{WorkPackage.table_name}.created_at DESC")
//      .includes(:status, :type)
//  }
//  // has_many :work_package_changes, through: :work_packages, source: :journals
//  // has_many :versions, -> {
//    order("#{Version.table_name}.effective_date DESC, #{Version.table_name}.name DESC")
//  }, dependent: :destroy
  // has_many :time_entries, dependent: :delete_all
  // has_many :queries, dependent: :delete_all
  // has_many :news, -> { includes(:author) }, dependent: :destroy
  // has_many :categories, -> { order("#{Category.table_name}.name") }, dependent: :delete_all
  // has_many :forums, -> { order("position ASC") }, dependent: :destroy
  // has_one :repository, dependent: :destroy
  // has_many :changesets, through: :repository
  // has_one :wiki, dependent: :destroy
  // Custom field for the project"s work_packages
//  has_and_belongs_to_many :work_package_custom_fields, -> {
//    order("#{CustomField.table_name}.position")
//  }, class_name: "WorkPackageCustomField",
//     join_table: "#{table_name_prefix}custom_fields_projects#{table_name_suffix}",
//     association_foreign_key: "custom_field_id"

//  acts_as_nested_set order_column: :name, dependent: :destroy

//  acts_as_customizable
//  acts_as_searchable columns: ["#{table_name}.name", "#{table_name}.identifier", "#{table_name}.description"], project_key: "id", permission: nil
//  acts_as_event title: Proc.new { |o| "#{Project.model_name.human}: #{o.name}" },
//                url: Proc.new { |o| { controller: "/projects", action: "show", id: o } },
//                author: nil,
//                datetime: :created_on

//  // validates :name,
//            presence: true,
//            length: { maximum: 255 }
//  // TODO: we temporarily disable this validation because it leads to failed tests
//  // it implicitly assumes a db:seed-created standard type to be present and currently
//  // neither development nor deployment setups are prepared for this
//  // validates_presence_of :types
//  // validates :identifier,
//            presence: true,
//            uniqueness: { case_sensitive: true },
//            length: { maximum: IDENTIFIER_MAX_LENGTH },
//            exclusion: RESERVED_IDENTIFIERS

//  // validates_associated :repository, :wiki
//  // starts with lower-case letter, a-z, 0-9, dashes and underscores afterwards
//  // validates :identifier,
//            format: { with: /\A[a-z][a-z0-9\-_]*\z/ },
//            if (: ->(p) { p.identifier_changed? }) {
//  // reserved words

//  friendly_id :identifier, use: :finders

//  before_destroy :delete_all_members
//  before_destroy :destroy_all_work_packages

//  // scope :has_module, ->(mod) {
//    where(["#{Project.table_name}.id IN (SELECT em.project_id FROM #{EnabledModule.table_name} em WHERE em.name=?)", mod.to_s])
//  }
//  // scope :public_projects, -> { where(is_public: true) }
//  // scope :visible, ->(user = User.current) { merge(Project.visible_by(user)) }
//  // scope :newest, -> { order(created_on: :desc) }

//   void visible?(user = User.current) {
//    active? and (is_public? or user.admin? or user.member_of?(self))
//  }

//   void copy_allowed?() {
//    User.current.allowed_to?(:copy_projects, self) && (parent.nil? || User.current.allowed_to?(:add_subprojects, parent))
//  }

//   void selectable_projects() {
//    Project.visible.select { |p| User.current.member_of? p }.sort_by(&:to_s)
//  }

//   void search_scope(query) {
//    // overwritten from Pagination::Model
//    visible.like(query)
//  }

//  // } timelines
//   Project(attributes = nil) {
//    super

//    initialized = (attributes || {}).stringify_keys
//    if ( !initialized.key?("identifier") && Setting.sequential_project_identifiers?) {
//      this->identifier = Project.next_identifier
//    }
//    if ( !initialized.key?("is_public")) {
//      this->is_public = Setting.default_projects_public?
//    }
//    if ( !initialized.key?("enabled_module_names")) {
//      this->enabled_module_names = Setting.default_projects_modules
//    }
//    if ( !initialized.key?("types") && !initialized.key?("type_ids")) {
//      this->types = ::Type.default
//    }
//  }

//   void possible_members(criteria, limit) {
//    Principal.active_or_registered.like(criteria).not_in_project(self).limit(limit)
//  }

//   void add_member(user, roles) {
//    members.build.tap { |m|
//      m.principal = user
//      m.roles = Array(roles)
//    }
//  }

//   void add_member!(user, roles) {
//    add_member(user, roles)
//    save
//  }

//  // Returns all projects the user is allowed to see.
//  //
//  // Employs the :view_project permission to perform the
//  // authorization check as the permissino is public, meaning it is granted
//  // to everybody having at least one role in a project regardless of the
//  // role"s permissions.
//   void visible_by(user = User.current) {
//    allowed_to(user, :view_project)
//  }

//  // Returns a ActiveRecord::Relation to find all projects for which
//  // +user+ has the given +permission+
//   void allowed_to(user, permission) {
//    Authorization.projects(permission, user)
//  }

//   void reload(*args) {
//    this->all_work_package_custom_fields = nil

//    super
//  }

//  // Returns the Systemwide and project specific activities
//   void activities(include_inactive = false) {
//    if ( include_inactive) {
//      all_activities
//    else
//      active_activities
//    }
//  }

//  // Will create a new Project specific Activity or update an existing one
//  //
//  // This will raise a ActiveRecord::Rollback if ( the TimeEntryActivity) {
//  // does not successfully save.
//   void update_or_create_time_entry_activity(id, activity_hash) {
//    if ( activity_hash.respond_to?(:has_key?) && activity_hash.has_key?("parent_id")) {
//      create_time_entry_activity_if_needed(activity_hash)
//    else
//      activity = project.time_entry_activities.find_by(id: id.to_i)
//      if ( activity) { activity.update_attributes(activity_hash) ;}
//    }
//  }

//  // Create a new TimeEntryActivity if ( it overrides a system TimeEntryActivity) {
//  //
//  // This will raise a ActiveRecord::Rollback if ( the TimeEntryActivity) {
//  // does not successfully save.
//   void create_time_entry_activity_if_needed(activity) {
//    if ( activity["parent_id"]) {

//      parent_activity = TimeEntryActivity.find(activity["parent_id"])
//      activity["name"] = parent_activity.name
//      activity["position"] = parent_activity.position

//      if ( Enumeration.overridding_change?(activity, parent_activity)) {
//        project_activity = time_entry_activities.create(activity)

//        if ( project_activity.new_record?) {
//          raise ActiveRecord::Rollback, "Overridding TimeEntryActivity was not successfully saved"
//        else
//          time_entries.where(["activity_id = ?", parent_activity.id])
//            .update_all("activity_id = #{project_activity.id}")
//        }
//      }
//    }
//  }

//  // Returns a :conditions SQL string that can be used to find the issues associated with this project.
//  //
//  // Examples:
//  //   project.project_condition(true)  => "(projects.id = 1 OR (projects.lft > 1 AND projects.rgt < 10))"
//  //   project.project_condition(false) => "projects.id = 1"
//   void project_condition(with_subprojects) {
//    cond = "#{Project.table_name}.id = #{id}"
//    if ( with_subprojects) { cond = "(#{cond} OR (#{Project.table_name}.lft > #{lft} AND #{Project.table_name}.rgt < #{rgt}))" ;}
//    cond
//  }

//  // Archives the project and its descendants
//   void archive() {
//    // Check that there is no issue of a non descendant project that is assigned
//    // to one of the project or descendant versions
//    v_ids = self_and_descendants.map(&:version_ids).flatten
//    if ( v_ids.any? && WorkPackage.includes(:project)) {
//                     .where(["(#{Project.table_name}.lft < ? OR #{Project.table_name}.rgt > ?)" +
//                        " AND #{WorkPackage.table_name}.fixed_version_id IN (?)", lft, rgt, v_ids])
//                     .references(:projects)
//                     .first
//      return false
//    }

//    Project.transaction {
//      archive!
//    }

//    true
//  }

//  // Unarchives the project
//  // All its ancestors must be active
//   void unarchive() {
//    if ( ancestors.detect { |a| !a.active? }) { return false ;}

//    update_attribute :status, STATUS_ACTIVE
//  }

//  // Returns an array of projects the project can be moved to
//  // by the current user
//   void allowed_parents() {
//    if ( this->allowed_parents) { return this->allowed_parents ;}

//    this->allowed_parents = Project.allowed_to(User.current, :add_subprojects)
//    this->allowed_parents = this->allowed_parents - self_and_descendants
//    if ( User.current.allowed_to?(:add_project, nil, global: true) || (!new_record? && parent.nil?)) {
//      this->allowed_parents << nil
//    }
//    unless parent.nil? || this->allowed_parents.empty? || this->allowed_parents.include?(parent)
//      this->allowed_parents << parent
//    }
//    this->allowed_parents
//  }

//   void allowed_parent?(p) {
//    p = guarantee_project_or_nil_or_false(p)
//    return false if ( p == false // have to explicitly check for false) {

//    !((p.nil? && persisted? && allowed_parents.empty?) ||
//      (p.present? && allowed_parents.exclude?(p)))
//  }

//  // Sets the parent of the project with authorization check
//   void set_allowed_parent!(p) {
//    if ( allowed_parent?(p)) { set_parent!(p) ;}
//  }

//  // Sets the parent of the project
//  // Argument can be either a Project, a String, a Fixnum or nil
//   void set_parent!(p) {
//    p = guarantee_project_or_nil_or_false(p)
//    return false if ( p == false // have to explicitly check for false) {

//    if ( p == parent && !p.nil?) {
//      // Nothing to {
//      true
//    } else if ( p.nil? || (p.active? && move_possible?(p))) {
//      // Insert the project so that target"s children or root projects stay alphabetically sorted
//      sibs = (p.nil? ? this->class.roots : p.children)
//      to_be_inserted_before = sibs.detect { |c| c.name.to_s.downcase > name.to_s.downcase }
//      if ( to_be_inserted_before) {
//        move_to_left_of(to_be_inserted_before)
//      } else if ( p.nil?) {
//        if ( sibs.empty?) {
//          // move_to_root adds the project in first (ie. left) position
//          move_to_root
//        else
//          move_to_right_of(sibs.last) unless self == sibs.last
//        }
//      else
//        // move_to_child_of adds the project in last (ie.right) position
//        move_to_child_of(p)
//      }
//      WorkPackage.update_versions_from_hierarchy_change(self)
//      true
//    else
//      // Can not move to the given target
//      false
//    }
//  }

//   void types_used_by_work_packages() {
//    ::Type.where(id: WorkPackage.where(project_id: project.id)
//                                .select(:type_id)
//                                .distinct)
//  }

//  // Returns an array of the types used by the project and its active sub projects
//   void rolled_up_types() {
//    this->rolled_up_types ||=
//      ::Type.joins(:projects)
//      .select("DISTINCT #{::Type.table_name}.*")
//      .where(["#{Project.table_name}.lft >= ? AND #{Project.table_name}.rgt <= ? AND #{Project.table_name}.status = #{STATUS_ACTIVE}", lft, rgt])
//      .order("#{::Type.table_name}.position")
//  }

//  // Closes open and locked project versions that are completed
//   void close_completed_versions() {
//    Version.transaction {
//      versions.where(status: %w(open locked)).each { |version|
//        if ( version.completed?) {
//          version.update_attribute(:status, "closed")
//        }
//      }
//    }
//  }

//  // Returns a scope of the Versions on subprojects
//   void rolled_up_versions() {
//    this->rolled_up_versions ||=
//      Version.includes(:project)
//      .where(["#{Project.table_name}.lft >= ? AND #{Project.table_name}.rgt <= ? AND #{Project.table_name}.status = #{STATUS_ACTIVE}", lft, rgt])
//      .references(:projects)
//  }

//  // Returns a scope of the Versions used by the project
//   void shared_versions() {
//    this->shared_versions ||= begin
//      r = root? ? self : root

//      Version.includes(:project)
//      .where("#{Project.table_name}.id = #{id}" +
//                                    " OR (#{Project.table_name}.status = #{Project::STATUS_ACTIVE} AND (" +
//                                          " #{Version.table_name}.sharing = "system"" +
//                                          " OR (#{Project.table_name}.lft >= #{r.lft} AND #{Project.table_name}.rgt <= #{r.rgt} AND #{Version.table_name}.sharing = "tree")" +
//                                          " OR (#{Project.table_name}.lft < #{lft} AND #{Project.table_name}.rgt > #{rgt} AND #{Version.table_name}.sharing IN ("hierarchy", "descendants"))" +
//                                          " OR (#{Project.table_name}.lft > #{lft} AND #{Project.table_name}.rgt < #{rgt} AND #{Version.table_name}.sharing = "hierarchy")" +
//                                          "))")
//      .references(:projects)
//    }
//  }

//  // Returns all versions a work package can be assigned to.  Opposed to
//  // #shared_versions this returns an array of Versions, not a scope.
//  //
//  // The main benefit is in scenarios where work packages" projects are eager
//  // loaded.  Because eager loading the project e.g. via
//  // WorkPackage.includes(:project).where(type: 5) will assign the same instance
//  // (same object_id) for every work package having the same project this will
//  // reduce the number of db queries when performing operations including the
//  // project"s versions.
//   void assignable_versions() {
//    this->all_shared_versions ||= shared_versions.with_status_open.to_a
//  }

//  // Returns a hash of project users grouped by role
//   void users_by_role() {
//    members.includes(:principal, :roles).inject({}) { |h, m|
//      m.roles.each { |r|
//        h[r] ||= []
//        h[r] << m.principal
//      }
//      h
//    }
//  }

//  // Deletes all project"s members
//   void delete_all_members() {
//    me = Member.table_name
//    mr = MemberRole.table_name
//    this->class.connection.delete("DELETE FROM #{mr} WHERE #{mr}.member_id IN (SELECT #{me}.id FROM #{me} WHERE #{me}.project_id = #{id})")
//    Member.where(project_id: id).destroy_all
//  }

//   void destroy_all_work_packages() {
//    work_packages.each { |wp|
//      begin
//        wp.reload
//        wp.destroy
//      rescue ActiveRecord::RecordNotFound => e
//      }
//    }
//  }

//  // Returns users that should be always notified on project events
//   void recipients() {
//    notified_users
//  }

//  // Returns the users that should be notified on project events
//   void notified_users() {
//    // TODO: User part should be extracted to User#notify_about?
//    notified_members = members.select { |member|
//      setting = member.principal.mail_notification

//      (setting == "selected" && member.mail_notification?) || setting == "all"
//    }

//    notified_members.map(&:principal)
//  }

//  // Returns an array of all custom fields enabled for project issues
//  // (explictly associated custom fields and custom fields enabled for all projects)
//  //
//  // Supports the :include option.
//   void all_work_package_custom_fields(options = {}) {
//    this->all_work_package_custom_fields ||= (
//      WorkPackageCustomField.for_all(options) + (
//        if ( options.include? :include) {
//          WorkPackageCustomField.joins(:projects)
//            .where(projects: { id: id })
//            .includes(options[:include]) // use #preload instead of #includes if ( join gets too big) {
//        else
//          work_package_custom_fields
//        }
//      )
//    ).uniq.sort
//  }

//   void project() {
//    self
//  }

//   void <=>(project) {
//    name.downcase <=> project.name.downcase
//  }

//   void to_s() {
//    name
//  }

//  // Returns a short description of the projects (first lines)
//   void short_description(length = 255) {
//    unless description.present?
//      return ""
//    }

//    description.gsub(/\A(.{#{length}}[^\n\r]*).*\z/m, "\1...").strip
//  }

//  // The earliest start date of a project, based on it"s issues and versions
//   void start_date() {
//    [
//      work_packages.minimum("start_date"),
//      shared_versions.map(&:effective_date),
//      shared_versions.map(&:start_date)
//    ].flatten.compact.min
//  }

//  // The latest finish date of an issue or version
//   void due_date() {
//    [
//      work_packages.maximum("due_date"),
//      shared_versions.map(&:effective_date),
//      shared_versions.map { |v| v.fixed_issues.maximum("due_date") }
//    ].flatten.compact.max
//  }

//   void overdue?() {
//    active? && !due_date.nil? && (due_date < Date.today)
//  }

//  // Returns the percent completed for this project, based on the
//  // progress on it"s versions.
//   void completed_percent(options = { include_subprojects: false }) {
//    if ( options.delete(:include_subprojects)) {
//      total = self_and_descendants.map(&:completed_percent).sum

//      total / self_and_descendants.count
//    else
//      if ( versions.count > 0) {
//        total = versions.map(&:completed_percent).sum

//        total / versions.count
//      else
//        100
//      }
//    }
//  }

//  // Return true if ( this project is allowed to { the specified action.) {
//  // action can be:
//  // * a parameter-like Hash (eg. controller: "/projects", action: "edit")
//  // * a permission Symbol (eg. :edit_project)
//   void allows_to?(action) {
//    if ( action.is_a? Hash) {
//      allowed_actions.include? "#{action[:controller]}/#{action[:action]}"
//    else
//      allowed_permissions.include? action
//    }
//  }

//   void module_enabled?(module_name) {
//    module_name = module_name.to_s
//    enabled_modules.any? { |m| m.name == module_name }
//  }

//   void enabled_module_names=(module_names) {
//    if ( module_names && module_names.is_a?(Array)) {
//      module_names = module_names.map(&:to_s).reject(&:blank?)
//      this->enabled_modules = module_names.map { |name| enabled_modules.detect { |mod| mod.name == name } || EnabledModule.new(name: name) }
//    else
//      enabled_modules.clear
//    }
//  }

//  // Returns an array of the enabled modules names
//   void enabled_module_names() {
//    enabled_modules.map(&:name)
//  }

//  // Returns an array of projects that are in this project"s hierarchy
//  //
//  // Example: parents, children, siblings
//   void hierarchy() {
//    parents = project.self_and_ancestors || []
//    descendants = project.descendants || []
//    parents | descendants // Set union
//  }

//  // Returns an auto-generated project identifier based on the last identifier used
//   void next_identifier() {
//    p = Project.order(Arel.sql("created_on DESC")).first
//    p.nil? ? nil : p.identifier.to_s.succ
//  }

  // builds up a project hierarchy helper structure for use with #project_tree_from_hierarchy
  //
  // it expects a simple list of projects with a #lft column (awesome_nested_set)
  // and returns a hierarchy based on #lft
  //
  // the result is a nested list of root level projects that contain their child projects
  // but, each entry is actually a ruby hash wrapping the project and child projects
  // the keys are :project and :children where :children is in the same format again
  //
  //   result = [ root_level_project_info_1, root_level_project_info_2, ... ]
  //
  // where each entry has the form
  //
  //   project_info = { project: the_project, children: [ child_info_1, child_info_2, ... ] }
  //
  // if ( a project has no children the :children array is just empty) {
  //
//   void build_projects_hierarchy(projects) {
//    ancestors = []
//    result    = []

//    projects.sort_by(&:lft).each { |project|
//      while (ancestors.any? && !project.is_descendant_of?(ancestors.last[:project])){
//        // before we pop back one level, we sort the child projects by name
//        if ( h[:project].name }) { ancestors.last[:children] = ancestors.last[:children].sort_by { |h| h[:project].name.downcase ;}
//        ancestors.pop
//      }

//      current_hierarchy = { project: project, children: [] }
//      current_tree      = ancestors.any? ? ancestors.last[:children] : result

//      current_tree << current_hierarchy
//      ancestors << current_hierarchy
//    }

//    // at the } the root level must be sorted as well
//    if ( h[:project].name }) { result.sort_by { |h| h[:project].name.downcase ;}
//  }

//   void project_tree_from_hierarchy(projects_hierarchy, level, &block) {
//    projects_hierarchy.each { |hierarchy|
//      project = hierarchy[:project]
//      children = hierarchy[:children]
//      yield project, level
//      // recursively show children
//      if ( children.any?) { project_tree_from_hierarchy(children, level + 1, &block) ;}
//    }
//  }

//  // Yields the given block for each project with its level in the tree
//   void project_tree(projects, &block) {
//    projects_hierarchy = build_projects_hierarchy(projects)
//    project_tree_from_hierarchy(projects_hierarchy, 0, &block)
//  }

//   void project_level_list(projects) {
//    list = []
//    project_tree(projects) { |project, level|
//      element = {
//        project: project,
//        level:   level
//      }

//      if ( block_given?) { element.merge!(yield(project)) ;}

//      list << element
//    }
//    list
//  }

//   void allowed_permissions() {
//    this->allowed_permissions ||= begin
//      names = enabled_modules.loaded? ? enabled_module_names : enabled_modules.pluck(:name)

//      OpenProject::AccessControl.modules_permissions(names).map(&:name)
//    }
//  }

//   void allowed_actions() {
//    this->actions_allowed ||= allowed_permissions
//                         .map { |permission| OpenProject::AccessControl.allowed_actions(permission) }
//                         .flatten
//  }

//  // Returns all the active Systemwide and project specific activities
//   void active_activities() {
//    overridden_activity_ids = time_entry_activities.map(&:parent_id)

//    if ( overridden_activity_ids.empty?) {
//      TimeEntryActivity.shared.active
//    else
//      system_activities_and_project_overrides
//    }
//  }

//  // Returns all the Systemwide and project specific activities
//  // (inactive and active)
//   void all_activities() {
//    overridden_activity_ids = time_entry_activities.map(&:parent_id)

//    if ( overridden_activity_ids.empty?) {
//      TimeEntryActivity.shared
//    else
//      system_activities_and_project_overrides(true)
//    }
//  }

//  // Returns the systemwide active activities merged with the project specific overrides
//   void system_activities_and_project_overrides(include_inactive = false) {
//    if ( include_inactive) {
//      TimeEntryActivity
//        .shared
//        .where(["id NOT IN (?)", time_entry_activities.map(&:parent_id)]) +
//        time_entry_activities
//    else
//      TimeEntryActivity
//        .shared
//        .active
//        .where(["id NOT IN (?)", time_entry_activities.map(&:parent_id)]) +
//        time_entry_activities.active
//    }
//  }

//  // Archives subprojects recursively
//   void archive!() {
//    children.each { |subproject|
//      subproject.send :archive!
//    }
//    update_attribute :status, STATUS_ARCHIVED
//  }

//   void possible_principles_condition() {
//    condition = if ( Setting.work_package_group_assignment?) {
//                  ["(#{Principal.table_name}.type=? OR #{Principal.table_name}.type=?)", "User", "Group"]
//                else
//                  ["(#{Principal.table_name}.type=?)", "User"]
//                }

//    condition[0] += " AND (#{User.table_name}.status=? OR #{User.table_name}.status=?) AND roles.assignable = ?"
//    condition << Principal::STATUSES[:active]
//    condition << Principal::STATUSES[:invited]
//    condition << true

//    sanitize_sql_array condition
//  }

  protected:

//   void guarantee_project_or_nil_or_false(p) {
//    if ( p.is_a?(Project)) {
//      p
//    } else if ( p.to_s.blank?) {
//      nil
//    else
//      p = Project.find_by(id: p)
//      return false unless p

//      p
//    }
//  }
};
}

}