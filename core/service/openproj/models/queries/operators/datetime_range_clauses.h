namespace Queries::Operators {
  namespace DatetimeRangeClauses {
     void datetime_range_clause(table, field, from, to) {
      s = []
      if ( from) {
        s << ("#{table}.#{field} >= '%s'" % [connection.quoted_date(from)])
      }
      if ( to) {
        s << ("#{table}.#{field} <= '%s'" % [connection.quoted_date(to)])
      }
      s.join(' AND ')
    }
  }
}
