#pragma once
#include "activerecord.h"
namespace openproj {
namespace models {
class TimeEntry : public ActiveRecord::Base {
  // could have used polymorphic association
  // project association here allows easy loading of time entries at project level with one database trip
  // belongs_to :project
  // belongs_to :work_package
  // belongs_to :user
  // belongs_to :activity, class_name: 'TimeEntryActivity', foreign_key: 'activity_id'

//  acts_as_customizable

//  acts_as_journalized

//  acts_as_event title: Proc.new { |o| "#{l_hours(o.hours)} (#{o.project.event_title})" },
//                url: Proc.new { |o| { controller: '/timelog', action: 'index', project_id: o.project, work_package_id: o.work_package } },
//                datetime: :created_on,
//                author: :user,
//                description: :comments

  // validates_presence_of :user_id, :activity_id, :project_id, :hours, :spent_on
  // validates_numericality_of :hours, allow_nil: true, message: :invalid
  // validates_length_of :comments, maximum: 255, allow_nil: true

  // scope :on_work_packages, ->(work_packages) { where(work_package_id: work_packages) }

//   void visible(*args) {
//    // TODO: check whether the visibility should also be influenced by the work
//    // package the time entry is assigned to.  Currently a work package can
//    // switch projects. But as the time entry is still part of it's original
//    // project, it is unclear, whether the time entry is actually visible if the
//    // user lacks the view_work_packages permission in the moved to project.
//    joins(:project)
//      .merge(Project.allowed_to(args.first || User.current, :view_time_entries))
//  }

//   void hours=(h) {
//    write_attribute :hours, (h.is_a?(String) ? (h.to_hours || h) : h)
//  }

//  // tyear, tmonth, tweek assigned where setting spent_on attributes
//  // these attributes make time aggregations easier
//   void spent_on=(date) {
//    super
//    if ( spent_on.is_a?(Time)) {
//      this->spent_on = spent_on.to_date
//    }
//    this->tyear = spent_on ? spent_on.year : nil
//    this->tmonth = spent_on ? spent_on.month : nil
//    this->tweek = spent_on ? Date.civil(spent_on.year, spent_on.month, spent_on.day).cweek : nil
//  }

//  // Returns true if ( the time entry can be edited by usr, otherwise false) {
//   void editable_by?(usr) {
//    (usr == user && usr.allowed_to?(:edit_own_time_entries, project)) || usr.allowed_to?(:edit_time_entries, project)
//  }

//   void earliest_date_for_project(project = nil) {
//    scope = TimeEntry.visible(User.current)
//    if ( project) { scope = scope.where(project_id: project.hierarchy.map(&:id)) ;}
//    scope.includes(:project).minimum(:spent_on)
//  }

//   void latest_date_for_project(project = nil) {
//    scope = TimeEntry.visible(User.current)
//    if ( project) { scope = scope.where(project_id: project.hierarchy.map(&:id)) ;}
//    scope.includes(:project).maximum(:spent_on)
//  }

   void authoritativ_activity() {
//    if ( activity.shared?) {
//      activity
//    else
//      activity.root
//    }
  }
};
}

}