namespace Queries::Operators {
  class ClosedWorkPackages : public Base {
    label 'closed_work_packages'
    set_symbol 'c'
    require_value false

     void sql_for_field(_values, _db_table, _db_field) {
      "#{Status.table_name}.is_closed=#{connection.quoted_true}"
    }
  }
}
