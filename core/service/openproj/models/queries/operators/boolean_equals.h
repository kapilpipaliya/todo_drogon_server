namespace Queries::Operators {
  class BooleanEquals : public Base {
    label 'equals'
    set_symbol '='

     void sql_for_field(values, db_table, db_field) {
      sql = ''

      if ( values.include?('f')) {
        sql = "#{db_table}.#{db_field} IS NULL OR "
      }

      sql += "#{db_table}.#{db_field} IN (" +
             values.map { |val| "'#{connection.quote_string(val)}'" }.join(',') + ')'

      sql
    }
  }
}
