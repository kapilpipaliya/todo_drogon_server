namespace Queries::Operators {
  class In : public Base {
    label 'in'
    set_symbol 't+'

    // extend DateRangeClauses

     void sql_for_field(values, db_table, db_field) {
      relative_date_range_clause(db_table, db_field, values.first.to_i, values.first.to_i)
    }
  }
}
