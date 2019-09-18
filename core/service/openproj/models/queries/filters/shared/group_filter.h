#pragma once

namespace openproj {
namespace models {
namespace Queries::Filters::Shared::GroupFilter {
//   void included(base) {
//    base.include(InstanceMethods)
//    base.extend(ClassMethods)
//  }

  namespace InstanceMethods {
     void allowed_values() {
//      this->allowed_values ||= begin
//        ::Group.pluck(:id).map { |g| [g, g.to_s] }
      }
    }

//     void available?() {
//      ::Group.exists?
//    }

     void type() {
//      :list_optional
    }

     void human_name() {
//      I18n.t('query_fields.member_of_group')
    }

     void where() {
//      case operator
//      when '='
//        "users.id IN (#{group_subselect})"
//      when '!'
//        "users.id NOT IN (#{group_subselect})"
//      when '*'
//        "users.id IN (#{any_group_subselect})"
//      when '!*'
//        "users.id NOT IN (#{any_group_subselect})"
//      }
    }

//    private:

     void group_subselect() {
//      User.in_group(values).select(:id).to_sql
    }

     void any_group_subselect() {
//      User.within_group([]).select(:id).to_sql
    }

  }

  namespace ClassMethods {
     void key() {
//      :group
    }
  }
}
}