namespace Queries::Operators {
  class NoneOrBlank : public None {
     void sql_for_field(_values, db_table, db_field) {
      "#{super} OR #{db_table}.#{db_field} = ''"
    }
  }
}
