namespace Queries::Operators {
  class BetweenDate : public Base {
    label 'between'
    set_symbol '<>d'

    extend DateRangeClauses

     void sql_for_field(values, db_table, db_field) {
      lower_boundary, upper_boundary = values.map { |v| v.blank? ? nil : Date.parse(v) }

      date_range_clause(db_table, db_field, lower_boundary, upper_boundary)
    }
  }
}
