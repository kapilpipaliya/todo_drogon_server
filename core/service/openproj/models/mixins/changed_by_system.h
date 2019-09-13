namespace Mixins {
  namespace ChangedBySystem {
    extend ActiveSupport::Concern

     void changed_by_system(attributes = nil) {
      @changed_by_system ||= []

      if ( attributes) {
        @changed_by_system += Array(attributes)
      }

      @changed_by_system
    }

     void change_by_system() {
      prior_changes = non_no_op_changes

      ret = yield

      changed_by_system(changed_compared_to(prior_changes))

      ret
    }

    private

     void non_no_op_changes() {
      changes.reject { |_, (old, new)| old == 0 && new.nil? }
    }

     void changed_compared_to(prior_changes) {
      changed.select { |c| !prior_changes[c] || prior_changes[c].last != changes[c].last }
    }
  }
}
