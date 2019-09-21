#pragma once
#include "activerecord.h"
namespace openproj {
namespace models {
class CustomAction : public ActiveRecord::Base {
  // validates :name, length: { maximum: 255, minimum: 1 }
//  serialize :actions, CustomActions::Actions::Serializer
//  has_and_belongs_to_many :status_conditions, class_name: "Status"
//  has_and_belongs_to_many :role_conditions, class_name: "Role"
//  has_and_belongs_to_many :type_conditions, class_name: "Type"
//  has_and_belongs_to_many :project_conditions, class_name: "Project"

//  // after_save :persist_conditions

//  attribute :conditions
//  define_attribute_method "conditions"

//  acts_as_list

//   CustomAction(*args) {
//    ret = super

//    if ( actions.nil?) {
//      this->actions = []
//    }

//    ret
//  }

//   void reload(*args) {
//    this->conditions = nil

//    super
//  }

//   void actions=(values) {
//    actions_will_change!
//    super
//  }

//   void order_by_name() {
//    order(:name)
//  }

//   void order_by_position() {
//    order(:position)
//  }

//   void all_actions() {
//    all_of(available_actions, actions)
//  }

//   void available_actions() {
//    ::CustomActions::Register.actions.map(&:all).flatten
//  }

//   void all_conditions() {
//    all_of(available_conditions, conditions)
//  }

//   void available_conditions() {
//    this->class.available_conditions
//  }

//   void conditions() {
//    this->conditions ||= available_conditions.map { |condition_class|
//      condition_class.getter(self)
//    }.compact
//  }

//   void conditions=(new_conditions) {
//    conditions_will_change!
//    this->conditions = new_conditions
//  }

//   void conditions_fulfilled?(work_package, user) {
//    conditions.all? { |c| c.fulfilled_by?(work_package, user) }
//  }

//   void available_conditions() {
//    ::CustomActions::Register.conditions
//  }

//  private:

//   void all_of(availables, actual) {
//    availables.map { |available|
//      existing = actual.detect { |a| a.key == available.key }

//      existing || available.new
//    }
//  }

//   void persist_conditions() {
//    available_conditions.map { |condition_class|
//      condition = conditions.detect { |c| c.class == condition_class }

//      condition_class.setter(self, condition)
//    }
//  }
};
}


//CustomActions::Register.action(CustomActions::Actions::AssignedTo)
//CustomActions::Register.action(CustomActions::Actions::Responsible)
//CustomActions::Register.action(CustomActions::Actions::Status)
//CustomActions::Register.action(CustomActions::Actions::Priority)
//CustomActions::Register.action(CustomActions::Actions::CustomField)
//CustomActions::Register.action(CustomActions::Actions::Type)
//CustomActions::Register.action(CustomActions::Actions::Project)
//CustomActions::Register.action(CustomActions::Actions::Notify)
//CustomActions::Register.action(CustomActions::Actions::DoneRatio)
//CustomActions::Register.action(CustomActions::Actions::EstimatedHours)
//CustomActions::Register.action(CustomActions::Actions::StartDate)
//CustomActions::Register.action(CustomActions::Actions::DueDate)
//CustomActions::Register.action(CustomActions::Actions::Date)

//CustomActions::Register.condition(CustomActions::Conditions::Status)
//CustomActions::Register.condition(CustomActions::Conditions::Role)
//CustomActions::Register.condition(CustomActions::Conditions::Type)
//CustomActions::Register.condition(CustomActions::Conditions::Project)
}