#pragma once
namespace openproject {
class CustomActions::UpdateService : public CustomActions::BaseService {
  // attr_accessor :user,
                :action

   UpdateService(action:, user:) {
    this->action = action
    this->user = user
  }

   void call(attributes:, &block) {
    super(attributes: attributes, action: action, &block)
  }
}
