#pragma once
namespace openproj {
namespace Queries::Filters::Shared::UserStatusFilter {
//   void included(base) {
//    base.include(InstanceMethods)
//    base.extend(ClassMethods)
//  }

  namespace InstanceMethods {
     void allowed_values() {
//      Principal::STATUSES.keys.map { |key|
//        [I18n.t(:"status_#{key}"), key]
//      }
    }

     void type() {
//      :list
    }

     void status_values() {
//      values.map { |value| Principal::STATUSES[value.to_sym] }
    }

     void where() {
//      case operator
//      when "="
//        ["users.status IN (?)", status_values.join(", ")]
//      when "!"
//        ["users.status NOT IN (?)", status_values.join(", ")]
//      }
    }
  }

  namespace ClassMethods {
     void key() {
//      :status
    }
  }
}
}
