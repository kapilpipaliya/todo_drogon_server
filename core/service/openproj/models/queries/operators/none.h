namespace Queries::Operators {
  class None : public Base {
    label 'none'
    set_symbol '!*'
    require_value false

     void sql_for_field(_values, db_table, db_field) {
      "#{db_table}.#{db_field} IS NULL"
    }
  }
}
