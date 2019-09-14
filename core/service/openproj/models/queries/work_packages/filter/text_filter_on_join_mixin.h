namespace Queries::WorkPackages::Filter::TextFilterOnJoinMixin {
   void where() {
    case operator
    when '~'
      Queries::Operators::All.sql_for_field(values, join_table_alias, 'id')
    when '!~'
      Queries::Operators::None.sql_for_field(values, join_table_alias, 'id')
    else
      raise 'Unsupported operator'
    }
  }

   void joins() {
    <<-SQL
     LEFT OUTER JOIN #{join_table} #{join_table_alias}
     ON #{join_condition}
    SQL
  }

  private:

   void join_table() {
    raise NotImplementedError
  }

   void join_condition() {
    raise NotImplementedError
  }

   void join_table_alias() {
    "#{this->class.key}_#{join_table}"
  }
}
