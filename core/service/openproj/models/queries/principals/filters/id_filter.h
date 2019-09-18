#pragma once
#include "../../../queries/principals/filters/principal_filter.h"
namespace openproj {
namespace models {
namespace Queries {
namespace Principals {
namespace Filters {
class IdFilter : public openproj::models::Queries::Principals::Filters::PrincipalFilter {
   void allowed_values() {
//    [["me", "me"]] // Not the whole truth but performes better than checking all IDs
  }

   void type() {
//    :list
  }

   void key() {
//    :id
  }

   void where() {
//    operator_strategy.sql_for_field(values_replaced, this->class.model.table_name, this->class.key)
  }

   void values_replaced() {
//    vals = values.clone

//    if ( vals.delete('me')) {
//      if ( User.current.logged?) {
//        vals.push(User.current.id.to_s)
//      else
//        vals.push('0')
//      }
//    }

//    vals
  }
};
}
}
}
}

}