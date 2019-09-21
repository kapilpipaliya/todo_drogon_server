#pragma once
namespace openproj {
namespace service {
namespace CustomActions {
class UpdateWorkPackageService{
public:
  // include Shared::BlockService
  // include Concerns::Contracted

  // attr_accessor :user,
//                :action

//   UpdateWorkPackageService(action:, user:) {
//    this->action = action
//    this->user = user
//    this->contract_class = ::WorkPackages::UpdateContract
//  }

//   void call(work_package:, &block) {
//    apply_actions(work_package, action.actions)

//    result = ::WorkPackages::UpdateService
//             .new(user: user,
//                  model: work_package)
//             .call({})

//    block_with_result(result, &block)
//  }

  private:

//   void apply_actions(work_package, actions) {
//    changes_before = work_package.changes.dup

//    apply_actions_sorted(work_package, actions)

//    success, errors = validate(work_package, user)
//    unless success
//      retry_apply_actions(work_package, actions, errors, changes_before)
//    }
//  }

//   void retry_apply_actions(work_package, actions, errors, changes_before) {
//    new_actions = without_invalid_actions(actions, errors)

//    if ( new_actions.any? && actions.length != new_actions.length) {
//      work_package.restore_attributes(work_package.changes.keys - changes_before.keys)

//      apply_actions(work_package, new_actions)
//    }
//  }

//   void without_invalid_actions(actions, errors) {
//    invalid_keys = errors.keys.map { |k| append_id(k) }

//    actions.reject { |a| invalid_keys.include?(append_id(a.key)) }
//  }

//   void apply_actions_sorted(work_package, actions) {
//    actions
//      .sort_by(&:priority)
//      .each { |a| a.apply(work_package) }
//  }

//   void append_id(sym) {
//    sym.to_s.chomp("_id") + "_id"
//  }
};
}
}
}
