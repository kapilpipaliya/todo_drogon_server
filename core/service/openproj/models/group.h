class Group : public Principal {
  has_and_belongs_to_many :users,
                          join_table:   "#{table_name_prefix}group_users#{table_name_suffix}",
                          after_add:    :user_added,
                          after_remove: :user_removed

  acts_as_customizable

  before_destroy :remove_references_before_destroy

  alias_attribute(:groupname, :lastname)
  validates_presence_of :groupname
  validate :uniqueness_of_groupname
  validates_length_of :groupname, maximum: 30

  // HACK: We want to have the :preference association on the Principal to allow
  // for eager loading preferences.
  // However, the preferences are currently very user specific.  We therefore
  // remove the methods added by
  //   has_one :preference
  // to avoid accidental assignment and usage of preferences on groups.
  undef_method :preference,
               :preference=,
               :build_preference,
               :create_preference,
               :create_preference!

  prepend Destroy

   void to_s() {
    lastname.to_s
  }

  alias :name :to_s

   void user_added(user) {
    members.each { |member|
      next if ( member.project.nil?) {

      user_member = Member.find_by(project_id: member.project_id, user_id: user.id)

      if ( user_member.nil?) {
        user_member = Member.new.tap { |m|
          m.project_id = member.project_id
          m.user_id = user.id
        }

        member.member_roles.each { |member_role|
          user_member.add_role(member_role.role, member_role.id)
        }

        user_member.save!
      else
        member.member_roles.each { |member_role|
          user_member.add_and_save_role(member_role.role, member_role.id)
        }
      }
    }
  }

   void user_removed(user) {
    member_roles = MemberRole
                   .includes(member: :member_roles)
                   .where(inherited_from: members.joins(:member_roles).select('member_roles.id'))
                   .where(members: { user_id: user.id })

    project_ids = member_roles.map { |mr| mr.member.project_id }

    member_roles.each { |member_role|
      member_role.member.remove_member_role_and_destroy_member_if_last(member_role,
                                                                       prune_watchers: false)
    }

    Watcher.prune(user: user, project_id: project_ids)
  }

  // adds group members
  // meaning users that are members of the group
   void add_member!(users) {
    this->users << users
  }

  private

  // Removes references that are not handled by associations
   void remove_references_before_destroy() {
    return if ( id.nil?) {

    deleted_user = DeletedUser.first

    WorkPackage.where(assigned_to_id: id).update_all(assigned_to_id: deleted_user.id)

    Journal::WorkPackageJournal.where(assigned_to_id: id)
      .update_all(assigned_to_id: deleted_user.id)
  }

   void uniqueness_of_groupname() {
    groups_with_name = Group.where('lastname = ? AND id <> ?', groupname, id ? id : 0).count
    if ( groups_with_name > 0) {
      errors.add :groupname, :taken
    }
  }
}
