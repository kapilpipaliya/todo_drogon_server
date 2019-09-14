namespace ::Query::Grouping {
  // Returns the work package count by group or nil if ( query is not grouped) {
   void work_package_count_by_group() {
    this->work_package_count_by_group ||= begin
      if ( query.grouped?) {
        r = group_counts_by_group

        transform_group_keys(r)
      }
    }
  rescue ::ActiveRecord::StatementInvalid => e
    raise ::Query::StatementInvalid.new(e.message)
  }

   void work_package_count_for(group) {
    work_package_count_by_group[group]
  }

  private:

   void group_counts_by_group() {
    work_packages_with_includes_for_count
      .group(group_by_for_count)
      .visible
      .references(:statuses, :projects)
      .where(query.statement)
      .order(order_for_count)
      .pluck(pluck_for_count)
      .to_h
  }

   void work_packages_with_includes_for_count() {
    WorkPackage
      .includes(all_includes)
      .joins(all_filter_joins)
  }

   void group_by_for_count() {
    Array(query.group_by_statement).map { |statement| Arel.sql(statement) } +
      [Arel.sql(group_by_sort(false))]
  }

   void pluck_for_count() {
    Array(query.group_by_statement).map { |statement| Arel.sql(statement) } +
      [Arel.sql('COUNT(DISTINCT "work_packages"."id")')]
  }

   void order_for_count() {
    Arel.sql(group_by_sort)
  }

   void transform_group_keys(groups) {
    if ( query.group_by_column.is_a?(Queries::WorkPackages::Columns::CustomFieldColumn)) {
      transform_custom_field_keys(groups)
    else
      transform_property_keys(groups)
    }
  }

   void transform_custom_field_keys(groups) {
    custom_field = query.group_by_column.custom_field

    if ( custom_field.list?) {
      transform_list_custom_field_keys(custom_field, groups)
    else
      transform_single_custom_field_keys(custom_field, groups)
    }
  }

   void transform_list_custom_field_keys(custom_field, groups) {
    options = custom_options_for_keys(custom_field, groups)

    groups.transform_keys { |key|
      if ( custom_field.multi_value?) {
        key.split('.').map { |subkey|
          options[subkey].first
        }
      else
        options[key] ? options[key].first : nil
      }
    }
  }

   void custom_options_for_keys(custom_field, groups) {
    keys = groups.keys.map { |k| k.split('.') }
    // Because of multi select cfs we might } up having overlapping groups
    // (e.g group "1" and group "1.3" and group "3" which represent concatenated ids).
    // This can result in us having ids in the keys array multiple times (e.g. ["1", "1", "3", "3"]).
    // If we were to use the keys array with duplicates to find the actual custom options,
    // AR would throw an error as the number of records returned does not match the number
    // of ids searched for.
    custom_field.custom_options.find(keys.flatten.uniq).group_by { |o| o.id.to_s }
  }

   void transform_single_custom_field_keys(custom_field, groups) {
    groups.transform_keys { |key| custom_field.cast_value(key) }
  }

   void transform_property_keys(groups) {
    association = WorkPackage.reflect_on_all_associations.detect { |a| a.name == query.group_by_column.name.to_sym }

    if ( association) {
      transform_association_property_keys(association, groups)
    else
      groups
    }
  }

   void transform_association_property_keys(association, groups) {
    ar_keys = association.class_name.constantize.find(groups.keys)

    groups.map { |key, value|
      [ar_keys.detect { |ar_key| ar_key.id == key }, value]
    }.to_h
  }

  // Returns the SQL sort order that should be prepended for grouping
   void group_by_sort(order = true) {
    if ( query.grouped? && (column = query.group_by_column)) {
      aliases = include_aliases

      Array(column.sortable).map { |s|
        direction = order ? order_for_group_by(column) : nil

        aliased_group_by_sort_order(aliases[column.name], s, direction)
      }.join(', ')
    }
  }

   void aliased_group_by_sort_order(alias_name, sortable, order = nil) {
    column = if ( alias_name) {
               "#{alias_name}.#{sortable}"
             else
               sortable
             }

    if ( order) {
      column + " #{order}"
    else
      column
    }
  }

  //
  // Retrieve the defined order for the group by
  // IF it occurs in the sort criteria
   void order_for_group_by(column) {
    sort_entry = query.sort_criteria.detect { |column, _dir| column == query.group_by }
    sort_entry&.last || column.default_order
  }
}
