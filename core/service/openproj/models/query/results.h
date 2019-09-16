#pragma once
//require_dependency 'query/group_by'
//require_dependency 'query/sums'

namespace openproj {
namespace QueryN {
class Results {
  // include ::QueryN::Grouping
  // include ::QueryN::Sums
  // include Redmine::I18n

  // attr_accessor :query

//   Results(query) {
//    this->query = query
//  }

  // Returns the work package count
//   void work_package_count() {
//    work_package_scope
//      .joins(all_filter_joins)
//      .includes(:status, :project)
//      .where(query.statement)
//      .references(:statuses, :projects)
//      .count
//  rescue ::ActiveRecord::StatementInvalid => e
//    raise ::QueryN::StatementInvalid.new(e.message)
//  }

//   void work_packages() {
//    work_package_scope
//      .where(query.statement)
//      .includes(all_includes)
//      .joins(all_joins)
//      .order(order_option)
//      .references(:projects)
//  }

  // Same as :work_packages, but returns a result sorted by the sort_criteria defined in the query.
  // Note: It escapes me, why this is not the default behaviour.
  // if ( there is a reason: This is a somewhat DRY way of using the sort criteria.) {
  // if ( there is no reason: The :work_package method can die over time and be replaced by this one.) {
//   void sorted_work_packages() {
//    work_packages.order(sort_criteria_array)
//  }

//   void versions() {
//    scope = Version
//            .visible

//    if ( query.project) {
//      scope.where(query.project_limiting_filter.where)
//    }

//    scope
//  }

//   void order_option() {
//    order_option = [group_by_sort].reject(&:blank?).join(', ')

//    if ( order_option.blank?) {
//      nil
//    else
//      Arel.sql(order_option)
//    }
//  }

  private:

//   void work_package_scope() {
//    WorkPackage
//      .visible
//      .merge(filter_merges)
//  }

//   void all_includes() {
//    (%i(status project) +
//      includes_for_columns(include_columns)).uniq
//  }

//   void all_joins() {
//    sort_criteria_joins + all_filter_joins
//  }

//   void includes_for_columns(column_names) {
//    column_names = Array(column_names)
//    (WorkPackage.reflections.keys.map(&:to_sym) & column_names.map(&:to_sym))
//  }

//   void custom_field_column?(name) {
//    name.to_s =~ /\Acf_\d+\z/
//  }

  //
  // Returns the columns that need to be included to allow:
  // * sorting
  // * grouping
//   void include_columns() {
//    columns = query.sort_criteria_columns.map { |column, _direction| column.association }

//    if ( query.group_by_column) {
//      columns << query.group_by_column.association
//    }

//    columns << all_filter_includes(query)

//    clean_symbol_list(columns)
//  }

//   void sort_criteria_joins() {
//    query
//      .sort_criteria_columns
//      .map { |column, _direction| column.sortable_join_statement(query) }
//      .compact
//  }

//   void sort_criteria_array() {
//    criteria = SortHelper::SortCriteria.new
//    criteria.available_criteria = aliased_sorting_by_column_name
//    criteria.criteria = query.sort_criteria
//    criteria.map_each { |criteria| criteria.map { |raw| Arel.sql raw } }
//  }

//   void aliased_sorting_by_column_name() {
//    sorting_by_column_name = query.sortable_key_by_column_name

//    aliases = include_aliases

//    reflection_includes.each { |inc|
//      sorting_by_column_name[inc.to_s] = Array(sorting_by_column_name[inc.to_s]).map { |column| "#{aliases[inc]}.#{column}" }
//    }

//    sorting_by_column_name
//  }

  // To avoid naming conflicts, joined tables are aliased if they are joined
  // more than once. Here, joining tables that are referenced by multiple
  // columns are of particular interest.
  //
  // Mirroring the way AR creates aliases for included/joined tables: Normally,
  // included/joined associations are not aliased and as such, they simply use
  // the table name. But if an association is joined/included that relies on a
  // table which an already joined/included association also relies upon, that
  // name is already taken in the DB query. Therefore, the #alias_candidate
  // method is used which will concatenate the pluralized association name with
  // the table name the association is defined for.
  //
  // There is no handling for cases when the same association is joined/included
  // multiple times as the rest of the code should prevent that.
//   void include_aliases() {
//    counts = Hash.new { |h, key|
//      h[key] = 0
//    }

//    reflection_includes.each_with_object({}) { |inc, hash|
//      reflection = WorkPackage.reflections[inc.to_s]
//      table_name = reflection.klass.table_name

//      hash[inc] = reflection_alias(reflection, counts[table_name])

//      counts[table_name] += 1
//    }
//  }

//   void reflection_includes() {
//    WorkPackage.reflections.keys.map(&:to_sym) & all_includes.map(&:to_sym)
//  }

//   void reflection_alias(reflection, count) {
//    if ( count.zero?) {
//      reflection.klass.table_name
//    else
//      reflection.alias_candidate(WorkPackage.table_name)
//    }
//  }

//   void all_filter_includes(query) {
//    query.filters.map(&:includes)
//  }

//   void all_filter_joins() {
//    query.filters.map(&:joins).flatten.compact
//  }

//   void filter_merges() {
//    query.filters.inject(::WorkPackage.unscoped) { |scope, filter|
//      scope = scope.merge(filter.scope)
//      scope
//    }
//  }

//   void clean_symbol_list(list) {
//    list.flatten.compact.uniq.map(&:to_sym)
//  }
};
}
}
