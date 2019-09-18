#pragma once
#include "base.h"
namespace openproj {
namespace models {
namespace Queries::Operators {
  class NotEquals : public Base {
//    label 'not_equals'
//    set_symbol '!'

//     void sql_for_field(values, db_table, db_field) {
//      // code expects strings (e.g. for quoting), but ints would work as well: unify them here
//      values = values.map(&:to_s)

//      sql = ''

//      if ( values.present?) {
//        sql = "(#{db_table}.#{db_field} IS NULL OR #{db_table}.#{db_field} NOT IN (" +
//              values.map { |val| "'#{connection.quote_string(val)}'" }.join(',') + '))'
//      else
//        // empty set of forbidden values allows all results
//        sql = '1=1'
//      }

//      sql
//    }
  };
}
}
}