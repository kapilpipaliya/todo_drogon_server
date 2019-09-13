namespace Queries::Operators {
  class OrderedWorkPackages : public Base {
    label 'open_work_packages'
    set_symbol 'ow'
    require_value false

     void sql_for_field(_values, _db_table, _db_field) {
      "#{OrderedWorkPackage.table_name}.position IS NOT NULL"
    }
  }
}
