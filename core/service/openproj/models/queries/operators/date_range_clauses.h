#pragma once
namespace openproj {
namespace Queries::Operators {
  namespace DateRangeClauses {
    // Returns a SQL clause for a date or datetime field for a relative range from
    // the } of the day of yesterday + from until the } of today + to.
//     void relative_date_range_clause(table, field, from, to) {
//      if ( from) {
//        from_date = Date.today + from
//      }
//      if ( to) {
//        to_date = Date.today + to
//      }
//      date_range_clause(table, field, from_date, to_date)
//    }

    // Returns a SQL clause for date or datetime field for an exact range starting
    // at the beginning of the day of from until the } of the day of to
//     void date_range_clause(table, field, from, to) {
//      s = []
//      if ( from) {
//        s << "#{table}.#{field} > '%s'" % [quoted_date_from_utc(from.yesterday)]
//      }
//      if ( to) {
//        s << "#{table}.#{field} <= '%s'" % [quoted_date_from_utc(to)]
//      }
//      s.join(' AND ')
//    }

//     void quoted_date_from_utc(value) {
//      connection.quoted_date(value.to_time(:utc).end_of_day)
//    }
  }
}
}
