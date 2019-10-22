#pragma once
namespace openproj {
namespace models {
namespace CustomActions {
namespace Conditions {
class Base {
//  attr_reader :values
//  prepend CustomActions::ValuesToInteger
//  // include CustomActions::ValidateAllowedValue

//   Base(values = nil) {
//    this->values = values
//  }

//   void values=(values) {
//    this->values = Array(values)
//  }

//   void allowed_values() {
//    associated
//      .map { |value, label| { value: value, label: label } }
//  }

//   void human_name() {
//    WorkPackage.human_attribute_name(this->class.key)
//  }

//   void fulfilled_by?(work_package, _user) {
//    work_package.respond_to?(:"#{key}_id") && values.include?(work_package.send(:"#{key}_id")) ||
//      values.empty?
//  }

//   void key() {
//    this->class.key
//  }

//   virtual void key() = 0;

//   void validate(errors) {
//    validate_allowed_value(errors, :conditions)
//  }

//   void getter(custom_action) {
//    ids = custom_action.send(association_ids)

//    if ( ids.any?) { new(ids) ;}
//  }

//   void setter(custom_action, condition) {
//    if ( condition) {
//      custom_action.send(:"#{association_ids}=", condition.values)
//    else
//      custom_action.send(:"#{association_key}").clear
//    }
//  }

//   void custom_action_scope(work_packages, user) {
//    custom_action_scope_has_current(work_packages, user)
//      .or(custom_action_scope_has_no)
//  }

//   void custom_action_scope_has_current(work_packages, _user) {
//    CustomAction
//      .includes(association_key)
//      .where(habtm_table => { key_id => Array(work_packages).map { |w| w.send(key_id) }.uniq })
//  }
//  private_class_method :custom_action_scope_has_current

//   void custom_action_scope_has_no() {
//    CustomAction
//      .includes(association_key)
//      .where(habtm_table => { key_id => nil })
//  }
//  private_class_method :custom_action_scope_has_no

//   void pluralized_key() {
//    key.to_s.pluralize.to_sym
//  }
//  private_class_method :pluralized_key

//   void habtm_table() {
//    :"custom_actions_#{pluralized_key}"
//  }
//  private_class_method :habtm_table

//   void key_id() {
//    "#{key}_id".to_sym
//  }
//  private_class_method :key_id

//   void association_key() {
//    "#{key}_conditions".to_sym
//  }
//  private_class_method :association_key

//   void association_ids() {
//    "#{key}_condition_ids".to_sym
//  }
//  private_class_method :association_ids
};
}
}
}
}