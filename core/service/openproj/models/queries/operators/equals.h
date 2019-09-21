#pragma once
#include "base.h"
namespace openproj {
namespace models {
namespace Queries::Operators {
  class Equals : public Base {
//    label "equals"
//    set_symbol "="

//     void sql_for_field(values, db_table, db_field) {
//      // code expects strings (e.g. for quoting), but ints would work as well: unify them here
//      values = values.map(&:to_s)

//      sql = ""

//      if ( values.present?) {
//        if ( values.include?("-1")) {
//          sql = "#{db_table}.#{db_field} IS NULL OR "
//        }

//        sql += "#{db_table}.#{db_field} IN (" +
//               values.map { |val| ""#{connection.quote_string(val)}"" }.join(",") + ")"
//      else
//        // empty set of allowed values produces no result
//        sql = "0=1"
//      }

//      sql
//    }
  };
}
}
}