#pragma once
#include "activerecord.h"
#include "models/Roles.h"
namespace openproj {
namespace models {
class Role : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::Roles {
public:
  // extend Pagination::Model

  // Built-in roles
enum AAA{
    NON_BUILTIN = 0,
    BUILTIN_NON_MEMBER = 1,
    BUILTIN_ANONYMOUS  = 2
};

//  // scope :builtin, ->(*args) {
//    if ( args.first == true) { compare = "not" ;}
//    where("#{compare} builtin = #{NON_BUILTIN}")
//  }

//  before_destroy :check_deletable
//  // has_many :workflows, dependent: :delete_all {
//     void copy_from_role(source_role) {
//      Workflow.copy(nil, source_role, nil, proxy_association.owner)
//    }
//  }

  // has_many :member_roles, dependent: :destroy
  // has_many :members, through: :member_roles
  // has_many :role_permissions

//  default_scope -> {
//    includes(:role_permissions)
//  }

//  acts_as_list

  // validates :name,
//            presence: true,
//            length: { maximum: 30 },
//            uniqueness: { case_sensitive: true }

   void givable() {
//    where(builtin: NON_BUILTIN)
//      .where(type: "Role")
//      .order(Arel.sql("position"))
  }

   void permissions() {
//    // prefer map over pluck as we will probably always load
//    // the permissions anyway
//    role_permissions.map(&:permission).map(&:to_sym)
  }

//   void permissions=(perms) {
//    not_included_yet = (perms.map(&:to_sym) - permissions).reject(&:blank?)
//    included_until_now = permissions - perms.map(&:to_sym)

//    remove_permission!(*included_until_now)

//    add_permission!(*not_included_yet)
//  }

//   void add_permission!(*perms) {
//    perms.each { |perm|
//      add_permission(perm)
//    }
//  }

//   void remove_permission!(*perms) {
//    return unless permissions.is_a?(Array)

//    perms = perms.map(&:to_s)

//    this->role_permissions = role_permissions.reject { |rp|
//      perms.include?(rp.permission)
//    }
//  }

  // Returns true if ( the role has the given permission) {
//   void has_permission?(perm) {
//    !permissions.nil? && permissions.include?(perm.to_sym)
//  }

//   void <=>(other) {
//    other ? position <=> other.position : -1
//  }

   void to_s() {
//    name
  }

  // Return true if ( the role is a builtin role) {
   bool builtin() {
//    builtin != NON_BUILTIN
  }

  // Return true if the role is a project member role
   bool member() {
//    !builtin?
  }

  // Return true if role is allowed to { the specified action
  // action can be:
  // * a parameter-like Hash (eg. controller: "/projects", action: "edit")
  // * a permission Symbol (eg. :edit_project)
//   void allowed_to?(action) {
//    if ( action.is_a? Hash) {
//      allowed_actions.include? "#{action[:controller]}/#{action[:action]}"
//    else
//      allowed_permissions.include? action
//    }
//  }

  // Return the builtin "non member" role.  If the role doesn"t exist,
  // it will be created on the fly.
//   void non_member() {
//    non_member_role = where(builtin: BUILTIN_NON_MEMBER).first
//    if ( non_member_role.nil?) {
//      non_member_role = create(name: "Non member", position: 0) { |role|
//        role.builtin = BUILTIN_NON_MEMBER
//      }
//      if ( non_member_role.new_record?) { raise "Unable to create the non-member role." ;}
//    }
//    non_member_role
//  }

  // Return the builtin "anonymous" role.  If the role doesn"t exist,
  // it will be created on the fly.
//   void anonymous() {
//    anonymous_role = where(builtin: BUILTIN_ANONYMOUS).first
//    if ( anonymous_role.nil?) {
//      anonymous_role = create(name: "Anonymous", position: 0) { |role|
//        role.builtin = BUILTIN_ANONYMOUS
//      }
//      if ( anonymous_role.new_record?) { raise "Unable to create the anonymous role." ;}
//    }
//    anonymous_role
//  }

//   void by_permission(permission) {
//    all.select { |role|
//      role.allowed_to? permission
//    }
//  }

//   void paginated_search(search, options = {}) {
//    paginate_scope! givable.like(search), options
//  }

  private:

//   void allowed_permissions() {
//    this->allowed_permissions ||= permissions + OpenProject::AccessControl.public_permissions.map(&:name)
//  }

//   void allowed_actions() {
//    this->actions_allowed ||= allowed_permissions.map { |permission|
//      OpenProject::AccessControl.allowed_actions(permission)
//    }.flatten
//  }

//   void check_deletable() {
//    if ( members.any?) { raise "Can"t delete role" ;}
//    if ( builtin?) { raise "Can"t delete builtin role" ;}
//  }

//   void add_permission(permission) {
//    if ( persisted?) {
//      role_permissions.create(permission: permission)
//    else
//      role_permissions.build(permission: permission)
//    }
//  }
};
}

}
