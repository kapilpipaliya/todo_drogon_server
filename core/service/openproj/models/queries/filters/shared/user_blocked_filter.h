namespace Queries::Filters::Shared::UserBlockedFilter {
   void included(base) {
    base.include(InstanceMethods)
    base.extend(ClassMethods)
  }

  namespace InstanceMethods {
     void allowed_values() {
      [[I18n.t(:status_blocked), :blocked]]
    }

     void type() {
      :list
    }

     void where() {
      User.blocked_condition(operator == '=')
    }
  }

  namespace ClassMethods {
     void key() {
      :blocked
    }
  }
}
