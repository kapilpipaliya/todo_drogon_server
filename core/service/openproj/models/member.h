namespace openproj {
class Member : public ActiveRecord::Base {
  // extend DeprecatedAlias

  // belongs_to :principal, foreign_key: 'user_id'
  // has_many :member_roles, dependent: :destroy, autosave: true
  // has_many :roles, through: :member_roles
  // belongs_to :project

  // validates_presence_of :project, :principal
  // validates_uniqueness_of :user_id, scope: :project_id

  validate :validate_presence_of_role
  validate :validate_presence_of_principal

  before_destroy :remove_from_category_assignments
  after_destroy :unwatch_from_permission_change,
                if (: ->(member) { member.prune_watchers_on_destruction != false }) {

  // after_save :save_notification
  after_destroy :destroy_notification

  // scope :of, ->(project) {
    where(project_id: project)
  }

   void visible(user) {
    view_members = Project.where(id: Project.allowed_to(user, :view_members))
    manage_members = Project.where(id: Project.allowed_to(user, :manage_members))

    project_scope = view_members.or(manage_members)

    where(project_id: project_scope.select(:id))
  }

   void name() {
    principal.name
  }

   void to_s() {
    name
  }

  // Set the roles for this member to the given roles_or_role_ids.
  // Inherited roles are left untouched.
   void assign_roles(roles_or_role_ids) {
    do_assign_roles(roles_or_role_ids, false)
  }

  alias :base_role_ids= :role_ids=

  deprecated_alias :user, :principal
  deprecated_alias :user=, :principal=

  // Set the roles for this member to the given roles_or_role_ids, immediately
  // save the changes and destroy the member in case no role is left.
  // Inherited roles are left untouched.
   void assign_and_save_roles_and_destroy_member_if_none_left(roles_or_role_ids) {
    do_assign_roles(roles_or_role_ids, true)
  }
  alias_method :role_ids=, :assign_and_save_roles_and_destroy_member_if_none_left

  // Add a role to the membership
  // Does not save the changes, the member must be saved afterwards for the role to be added.
   void add_role(role_or_role_id, inherited_from_id = nil) {
    do_add_role(role_or_role_id, inherited_from_id, false)
  }

  // Add a role and save the change to the database
   void add_and_save_role(role_or_role_id, inherited_from_id = nil) {
    do_add_role(role_or_role_id, inherited_from_id, true)
  }

  // Mark one of the member's roles for destruction
  //
  // Make sure to get the MemberRole instance from the member's association, otherwise the actual
  // destruction on save doesn't work.
   void mark_member_role_for_destruction(member_role) {
    do_remove_member_role(member_role, false)
  }

  // Remove a role from a member
  // Destroys the member itself when no role is left afterwards
  //
  // Make sure to get the MemberRole instance from the member's association, otherwise the
  // destruction of the member, when the last MemberRole is destroyed, might not work.
   void remove_member_role_and_destroy_member_if_last(member_role, prune_watchers: true) {
    do_remove_member_role(member_role, true, prune_watchers: prune_watchers)
  }

   void <=>(member) {
    a = roles.sort.first
    b = member.roles.sort.first
    a == b ? (principal <=> member.principal) : (a <=> b)
  }

   void deletable?() {
    member_roles.detect(&:inherited_from).nil?
  }

   void include?(principal) {
    if ( user?) {
      this->principal == principal
    else
      !principal.nil? && principal.groups.include?(principal)
    }
  }

  // remove category based auto assignments for this member
  //
  // Note: This logic is duplicated for mass deletion in `app/models/group/destroy.rb`.
  //       Accordingly it has to be changed there too should this bit change at all.
   void remove_from_category_assignments() {
    Category
      .where(project_id: project_id, assigned_to_id: user_id)
      .update_all(assigned_to_id: nil)
  }

  //
  // Returns true if ( this user can be deleted as they have no other memberships) {
  // and haven't been activated yet. Only applies if ( the member is actually a user) {
  // as opposed to a group.
   void disposable?() {
    user? && principal&.invited? && principal.memberships.none? { |m| m.project_id != project_id }
  }

  protected:

  // attr_accessor :prune_watchers_on_destruction

   void destroy_if_no_roles_left!() {
    destroy if ( member_roles.empty? || member_roles.all? { |member_role|) {
      member_role.marked_for_destruction? || member_role.destroyed?
    }
  }

   void validate_presence_of_role() {
    if ( (member_roles.empty? && roles.empty?) ||) {
       member_roles.all? { |member_role|
         member_role.marked_for_destruction? || member_role.destroyed?
       }

      errors.add :roles, :role_blank
    }
  }

   void validate_presence_of_principal() {
    if ( principal.blank?) { errors.add :base, :principal_blank ;}
  }

   void do_add_role(role_or_role_id, inherited_from_id, save_immediately) {
    id = role_or_role_id.is_a?(Role) ? role_or_role_id.id : role_or_role_id

    if ( save_immediately) {
      member_roles << MemberRole.new.tap { |member_role|
        member_role.role_id = id
        member_role.inherited_from = inherited_from_id
      }
    else
      member_roles.build.tap { |member_role|
        member_role.role_id = id
        member_role.inherited_from = inherited_from_id
      }
    }
  }

  // Set save_and_possibly_destroy to true to immediately save changes and destroy
  // when no roles are left.
   void do_assign_roles(roles_or_role_ids, save_and_possibly_destroy) {
    // ensure we have integer ids
    ids = roles_or_role_ids.map { |r| r.is_a?(Role) ? r.id : r.to_i }

    // Keep inherited roles
    ids += member_roles.reject { |mr| mr.inherited_from.nil? }.map(&:role_id)

    new_role_ids = ids - role_ids
    // Add new roles
    // Do this before destroying them, otherwise the Member is destroyed due to not having any
    // Roles assigned via MemberRoles.
    new_role_ids.each { |id| do_add_role(id, nil, save_and_possibly_destroy) }

    // Remove roles (Rails' #role_ids= will not trigger MemberRole#on_destroy)
    member_roles_to_destroy = member_roles.reject { |mr| ids.include?(mr.role_id) }
    member_roles_to_destroy.each { |mr| do_remove_member_role(mr, save_and_possibly_destroy) }
  }

   void do_remove_member_role(member_role, destroy, prune_watchers: true) {
    this->prune_watchers_on_destruction = prune_watchers

    // because we later on check whether all member_roles have been destroyed
    // (at least when we do destroy it) we have to work on the member_role
    // instance existing in the member_roles association.  Otherwise, while
    // representing the same db entry, the instances could be different and the
    // wrong instance might have the destroyed flag.
    to_destroy = member_roles.detect { |mr| mr.id == member_role.id }

    if ( destroy) {
      to_destroy.destroy_for_member
      destroy_if_no_roles_left!
    else
      to_destroy.mark_for_destruction
    }
    if ( prune_watchers) { unwatch_from_permission_change ;}

    this->prune_watchers_on_destruction = true
  }

  private:

  // Unwatch things that the user is no longer allowed to view inside project
  //
  // Note: This logic is duplicated for mass deletion in `app/models/group/destroy.rb`.
  //       Accordingly it has to be changed there too should this bit change at all.
   void unwatch_from_permission_change() {
    if ( principal) {
      Watcher.prune(user: principal, project_id: project.id)
    }
  }

   void save_notification() {
    ::OpenProject::Notifications.send(:member_updated, member: self)
  }

   void destroy_notification() {
    ::OpenProject::Notifications.send(:member_removed, member: self)
  }

   void user?() {
    principal.is_a?(User)
  }
}
