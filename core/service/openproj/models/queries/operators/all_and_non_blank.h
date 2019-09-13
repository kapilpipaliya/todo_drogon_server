namespace Queries::Operators {
  class AllAndNonBlank : public All {
     void sql_for_field(_values, db_table, db_field) {
      "#{super} AND #{db_table}.#{db_field} <> ''"
    }
  }
}
