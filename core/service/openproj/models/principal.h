#pragma once
#include "activerecord.h"
namespace openproj {
class Principal : public ActiveRecord::Base {
  // Account statuses
  // Code accessing the keys assumes they are ordered, which they are since Ruby 1.9
//  STATUSES = {
//    builtin: 0,
//    active: 1,
//    registered: 2,
//    locked: 3,
//    invited: 4
//  }.freeze

//  this->table_name = "#{table_name_prefix}users#{table_name_suffix}"

//  // has_one :preference,
//          dependent: :destroy,
//          class_name: 'UserPreference',
//          foreign_key: 'user_id'
//  // has_many :members, foreign_key: 'user_id', dependent: :destroy
//  // has_many :memberships, -> {
//    includes(:project, :roles)
//      .where(projects: { status: Project::STATUS_ACTIVE })
//      .order(Arel.sql('projects.name ASC'))
    // haven't been able to produce the order using hashes
//  },
//           class_name: 'Member',
//           foreign_key: 'user_id'
//  // has_many :projects, through: :memberships
//  // has_many :categories, foreign_key: 'assigned_to_id', dependent: :nullify

//  // scope :active, -> { where(status: STATUSES[:active]) }

//  // scope :active_or_registered, -> {
//    where(status: [STATUSES[:active], STATUSES[:registered], STATUSES[:invited]])
//  }

//  // scope :active_or_registered_like, ->(query) { active_or_registered.like(query) }

//  // scope :in_project, ->(project) {
//    where(id: Member.of(project).select(:user_id))
//  }

//  // scope :not_in_project, ->(project) {
//    where.not(id: Member.of(project).select(:user_id))
//  }

//  // Active non-anonymous principals scope
//  // scope :not_builtin, -> {
//    where("#{Principal.table_name}.status <> #{STATUSES[:builtin]}")
//  }

//  // scope :like, ->(q) {
//    firstnamelastname = "((firstname || ' ') || lastname)"
//    lastnamefirstname = "((lastname || ' ') || firstname)"

//    s = "%#{q.to_s.downcase.strip.tr(',', '')}%"

//    where(['LOWER(login) LIKE :s OR ' +
//             "LOWER(#{firstnamelastname}) LIKE :s OR " +
//             "LOWER(#{lastnamefirstname}) LIKE :s OR " +
//             'LOWER(mail) LIKE :s',
//           { s: s }])
//      .order(:type, :login, :lastname, :firstname, :mail)
//  }

//  before_create :set_default_empty_values

//   void name(_formatter = nil) {
//    to_s
//  }

//   void possible_members(criteria, limit) {
//    Principal.active_or_registered_like(criteria).limit(limit)
//  }

//   void search_scope_without_project(project, query) {
//    active_or_registered_like(query).not_in_project(project)
//  }

//   void order_by_name() {
//    order(UserN::USER_FORMATS_STRUCTURE[Setting.user_format].map(&:to_s))
//  }

//   void me() {
//    where(id: User.current.id)
//  }

//   void in_visible_project(user = User.current) {
//    in_project(Project.visible(user))
//  }

//   void in_visible_project_or_me(user = User.current) {
//    in_visible_project(user)
//      .or(me)
//  }

//   void status_name() {
//    // Only Users should have another status than active.
//    // User defines the status values and other classes like Principal
//    // shouldn't know anything about them. Nevertheless, some functions
//    // want to know the status for other Principals than User.
//    raise 'Principal has status other than active' unless status == STATUSES[:active]

//    'active'
//  }

//   void active_or_registered?() {
//    [STATUSES[:active], STATUSES[:registered], STATUSES[:invited]].include?(status)
//  }

  //
  // Allows the API and other sources to determine locking actions
  // on represented collections of children of Principals.
  // Must be overriden by User
//   void lockable?() {
//    false
//  }

  //
  // Allows the API and other sources to determine unlocking actions
  // on represented collections of children of Principals.
  // Must be overriden by User
//   void activatable?() {
//    false
//  }

//   void <=>(other) {
//    if ( this->class.name == other.class.name) {
//      to_s.downcase <=> other.to_s.downcase
//    else
//      // groups after users
//      other.class.name <=> this->class.name
//    }
//  }

  protected:

  // Make sure we don't try to insert NULL values (see #4632)
//   void set_default_empty_values() {
//    this->login ||= ''
//    this->firstname ||= ''
//    this->lastname ||= ''
//    this->mail ||= ''
//    true
//  }

  // extend Pagination::Model
};
}

