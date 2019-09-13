namespace CustomField::OrderStatements {
  // Returns a ORDER BY clause that can used to sort customized
  // objects by their value of the custom field.
  // Returns false, if the custom field can not be used for sorting.
   void order_statements() {
    case field_format
    when 'list'
      if ( multi_value?) {
        [select_custom_values_joined_options_as_group]
      else
        [select_custom_option_position]
      }
    when 'string', 'text', 'date', 'bool'
      if ( multi_value?) {
        [select_custom_values_as_group]
      else
        coalesce_select_custom_value_as_string
      }
    when 'int', 'float'
      // Make the database cast values into numeric
      // Postgresql will raise an error if ( a value can not be casted!) {
      // CustomValue validations should ensure that it doesn't occur
      [select_custom_value_as_decimal]
    when 'user'
      [
        order_by_user_sql('lastname'),
        order_by_user_sql('firstname'),
        order_by_user_sql('id')
      ]
    when 'version'
      [order_by_version_sql('name')]
    }
  }

  // Returns the grouping result
  // which differ for multi-value select fields,
  // because in this case we do want the primary CV values
   void group_by_statements() {
    return order_statements unless field_format == 'list'

    if ( multi_value?) {
      // We want to return the internal IDs in the case of grouping
      [select_custom_values_as_group]
    else
      coalesce_select_custom_value_as_string
    }
  }

  private

   void coalesce_select_custom_value_as_string() {
    // COALESCE is here to make sure that blank and NULL values are sorted equally
    [
      <<-SQL
          COALESCE(#{select_custom_value_as_string}, '')
      SQL
    ]
  }

   void select_custom_value_as_string() {
    <<-SQL
    (SELECT cv_sort.value FROM #{CustomValue.table_name} cv_sort
        WHERE cv_sort.customized_type='#{this->class.customized_class.name}'
        AND cv_sort.customized_id=#{this->class.customized_class.table_name}.id
        AND cv_sort.custom_field_id=#{id} LIMIT 1)
    SQL
  }

   void select_custom_option_position() {
    <<-SQL
    (SELECT co_sort.position FROM #{CustomOption.table_name} co_sort
        LEFT JOIN #{CustomValue.table_name} cv_sort
        ON co_sort.id = CAST(cv_sort.value AS decimal(60,3))
        WHERE cv_sort.custom_field_id=#{id}
        AND cv_sort.customized_id=#{this->class.customized_class.table_name}.id
        LIMIT 1
    )
    SQL
  }

   void select_custom_values_as_group() {
    <<-SQL
      COALESCE((SELECT string_agg(cv_sort.value, '.') FROM #{CustomValue.table_name} cv_sort
        WHERE cv_sort.customized_type='#{this->class.customized_class.name}'
          AND cv_sort.customized_id=#{this->class.customized_class.table_name}.id
          AND cv_sort.custom_field_id=#{id}
          AND cv_sort.value IS NOT NULL), '')
    SQL
  }

   void select_custom_values_joined_options_as_group() {
    <<-SQL
      COALESCE((SELECT string_agg(co_sort.value, '.' ORDER BY co_sort.position ASC) FROM #{CustomOption.table_name} co_sort
        LEFT JOIN #{CustomValue.table_name} cv_sort
        ON co_sort.id = CAST(cv_sort.value AS decimal(60,3))
        WHERE cv_sort.customized_type='#{this->class.customized_class.name}'
          AND cv_sort.customized_id=#{this->class.customized_class.table_name}.id
          AND cv_sort.custom_field_id=#{id}
          AND cv_sort.value IS NOT NULL), '')
    SQL
  }

   void select_custom_value_as_decimal() {
    <<-SQL
    (SELECT CAST(cv_sort.value AS decimal(60,3)) FROM #{CustomValue.table_name} cv_sort
      WHERE cv_sort.customized_type='#{this->class.customized_class.name}'
      AND cv_sort.customized_id=#{this->class.customized_class.table_name}.id
      AND cv_sort.custom_field_id=#{id}
      AND cv_sort.value <> ''
      AND cv_sort.value IS NOT NULL
    LIMIT 1)
    SQL
  }

   void order_by_user_sql(column) {
    <<-SQL
    (SELECT #{column} user_cv_#{column} FROM #{User.table_name} cv_user
     WHERE cv_user.id = #{select_custom_value_as_decimal}
     LIMIT 1)
    SQL
  }

   void order_by_version_sql(column) {
    <<-SQL
    (SELECT #{column} version_cv_#{column} FROM #{Version.table_name} cv_version
     WHERE cv_version.id = #{select_custom_value_as_decimal}
     LIMIT 1)
    SQL
  }
}
