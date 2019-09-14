namespace WorkPackage::CustomActions {
  // extend ActiveSupport::Concern

  included {
     void custom_actions(user) {
      this->custom_actions = CustomAction
                        .available_conditions
                        .inject(CustomAction.all) { |scope, condition|
        scope.merge(condition.custom_action_scope(self, user))
      }
    }
  }
}
