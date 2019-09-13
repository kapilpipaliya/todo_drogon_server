namespace Queries::Operators {
  class Today : public Base {
    label 'today'
    set_symbol 't'
    require_value false

    extend DateRangeClauses

     void sql_for_field(_values, db_table, db_field) {
      relative_date_range_clause(db_table, db_field, 0, 0)
    }
  }
}
