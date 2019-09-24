#pragma once

#include "activerecord.h"
#include "Types.h"
namespace openproj {
namespace models {
class Type : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::Types {
  // extend Pagination::Model

  // Work Package attributes for this type
  // and constraints to specifc attributes (by plugins).
  // include ::TypeN::Attributes
  // include ::TypeN::AttributeGroups

//  before_destroy :check_integrity

  // has_many :work_packages
  // has_many :workflows, dependent: :delete_all {
//     void copy_from_type(source_type) {
//      Workflow.copy(source_type, nil, proxy_association.owner, nil)
//    }
//  }

//  has_and_belongs_to_many :projects

//  has_and_belongs_to_many :custom_fields,
//                          class_name: "WorkPackageCustomField",
//                          join_table: "#{table_name_prefix}custom_fields_types#{table_name_suffix}",
//                          association_foreign_key: "custom_field_id"

  // belongs_to :color,
//             class_name:  "Color",
//             foreign_key: "color_id"

//  acts_as_list

  // validates :name,
//            presence: true,
//            uniqueness: { case_sensitive: true },
//            length: { maximum: 255 }

  // validates_inclusion_of :is_default, :is_milestone, in: [true, false]

//  default_scope { order("position ASC") }

  // scope :without_standard, -> {
//    where(is_standard: false)
//      .order(:position)
//  }

//   void to_s; name }() {

//   void <=>(other) {
//    name <=> other.name
//  }

//   void statuses(types) {
//    workflow_table, status_table = [Workflow, Status].map(&:arel_table)
//    old_id_subselect, new_id_subselect = [:old_status_id, :new_status_id].map { |foreign_key|
//      workflow_table.project(workflow_table[foreign_key]).where(workflow_table[:type_id].in(types))
//    }
//    Status.where(status_table[:id].in(old_id_subselect).or(status_table[:id].in(new_id_subselect)))
//  }

//   void standard_type() {
//    ::Type.where(is_standard: true).first
//  }

//   void default() {
//    ::Type.where(is_default: true)
//  }

//   void enabled_in(project) {
//    ::Type.includes(:projects).where(projects: { id: project })
//  }

//   void statuses(include_default: false) {
//    if ( new_record?) {
//      Status.none
//    } else if ( include_default) {
//      ::Type
//        .statuses([id])
//        .or(Status.where_default)
//    else
//      ::Type.statuses([id])
//    }
//  }

//   void enabled_in?(object) {
//    object.types.include?(self)
//  }

//   void valid_transition?(status_id_a, status_id_b, roles) {
//    transition_exists?(status_id_a, status_id_b, roles.map(&:id))
//  }

  private:

   void check_integrity() {
//    if ( WorkPackage.where(type_id: id).any?) { raise "Can"t delete type" ;}
  }

//   void transition_exists?(status_id_a, status_id_b, role_ids) {
//    workflows
//      .where(old_status_id: status_id_a,
//             new_status_id: status_id_b,
//             role_id: role_ids)
//      .any?
//  }
};
}

}
