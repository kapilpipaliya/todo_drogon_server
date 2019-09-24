#pragma once
#include "activerecord.h"
#include "Statuses.h"
namespace openproj {
namespace models {
class Status : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::Statuses {
  // extend Pagination::Model

//  default_scope { order_by_position }
//  before_destroy :check_integrity
//  // has_many :workflows, foreign_key: "old_status_id"
//  acts_as_list

//  // belongs_to :color, class_name: "Color", foreign_key: "color_id"

//  before_destroy :delete_workflows

//  // validates :name,
//            presence: true,
//            uniqueness: { case_sensitive: false },
//            length: { maximum: 30 }

//  // validates_inclusion_of :default_done_ratio, in: 0..100, allow_nil: true

//  // after_save :unmark_old_default_value, if (: :is_default?) {

//   void unmark_old_default_value() {
//    Status.where.not(id: id).update_all(is_default: false)
//  }

//  // Returns the default status for new issues
//   void default() {
//    where_default.first
//  }

//   void where_default() {
//    where(is_default: true)
//  }

//  // Update all the +Issues+ setting their done_ratio to the value of their +Status+
//   void update_work_package_done_ratios() {
//    if ( WorkPackage.use_status_for_done_ratio?) {
//      Status.where(["default_done_ratio >= 0"]).each { |status|
//        WorkPackage
//          .where(["status_id = ?", status.id])
//          .update_all(["done_ratio = ?", status.default_done_ratio])
//      }
//    }

//    WorkPackage.use_status_for_done_ratio?
//  }

//  // Returns an array of all statuses the given role can switch to
//   void new_statuses_allowed_to(roles, type, author = false, assignee = false) {
//    this->class.new_statuses_allowed(self, roles, type, author, assignee)
//  }

//   void new_statuses_allowed(status, roles, type, author = false, assignee = false) {
//    if ( roles.present? && type.present?) {
//      status_id = status.try(:id) || 0

//      workflows = Workflow
//                  .from_status(status_id,
//                               type.id,
//                               roles.map(&:id),
//                               author,
//                               assignee)

//      Status.where(id: workflows.select(:new_status_id))
//    else
//      Status.where("1 = 0")
//    }
//  }

//   void order_by_position() {
//    order(:position)
//  }

//   void <=>(status) {
//    position <=> status.position
//  }

//   void to_s; name }() {

   void is_readonly() {
//    return false unless can_readonly?

//    super
  }
//  alias :is_readonly? :is_readonly

  //
  // Overrides cache key so that changes to EE state are reflected
   void cache_key() {
//    super + "/" + can_readonly?.to_s
  }

//   void can_readonly?() {
//    EnterpriseToken.allows_to?(:readonly_work_packages)
//  }

  private:

   void check_integrity() {
//    if ( WorkPackage.where(status_id: id).exists?) { raise "Can"t delete status" ;}
  }

  // Deletes associated workflows
   void delete_workflows() {
//    Workflow
//      .where(old_status_id: id)
//      .or(Workflow.where(new_status_id: id))
//      .delete_all
  }
};
}

}
