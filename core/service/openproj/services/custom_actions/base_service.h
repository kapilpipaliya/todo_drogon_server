#pragma once
namespace openproj {
namespace service {
namespace CustomActions {
class BaseService {
public:
  // include Shared::BlockService

  // attr_accessor :user

//   void call(attributes:,
//           action:,
//           &block)
//    set_attributes(action, attributes)

//    contract = CustomActions::CUContract.new(action)
//    result = ServiceResult.new(success: contract.validate && action.save,
//                               result: action,
//                               errors: contract.errors)

//    block_with_result(result, &block)
//  }

  private:

//   void set_attributes(action, attributes) {
//    actions_attributes = attributes.delete(:actions)
//    conditions_attributes = attributes.delete(:conditions)
//    action.attributes = attributes

//    if ( actions_attributes) { set_actions(action, actions_attributes.symbolize_keys) ;}
//    if ( conditions_attributes) { set_conditions(action, conditions_attributes.symbolize_keys) ;}
//  }

//   void set_actions(action, actions_attributes) {
//    existing_action_keys = action.actions.map(&:key)

//    remove_actions(action, existing_action_keys - actions_attributes.keys)
//    update_actions(action, actions_attributes.slice(*existing_action_keys))
//    add_actions(action, actions_attributes.slice(*(actions_attributes.keys - existing_action_keys)))
//  }

//   void remove_actions(action, keys) {
//    keys.each { |key|
//      remove_action(action, key)
//    }
//  }

//   void update_actions(action, key_values) {
//    key_values.each { |key, values|
//      update_action(action, key, values)
//    }
//  }

//   void add_actions(action, key_values) {
//    key_values.each { |key, values|
//      add_action(action, key, values)
//    }
//  }

//   void update_action(action, key, values) {
//    action.actions.detect { |a| a.key == key }.values = values
//  }

//   void add_action(action, key, values) {
//    action.actions << available_action_for(action, key).new(values)
//  }

//   void remove_action(action, key) {
//    action.actions.reject! { |a| a.key == key }
//  }

//   void set_conditions(action, conditions_attributes) {
//    action.conditions = conditions_attributes.map { |key, values|
//      available_condition_for(action, key).new(values)
//    }
//  }

//   void available_action_for(action, key) {
//    action.available_actions.detect { |a| a.key == key } || CustomActions::Actions::Inexistent
//  }

//   void available_condition_for(action, key) {
//    action.available_conditions.detect { |a| a.key == key } || CustomActions::Conditions::Inexistent
//  }
};
}
}
}
