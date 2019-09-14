class Query : public ActiveRecord::Base {
  // include Timelines
  // include Highlighting
  // include ManualSorting
  // include Queries::AvailableFilters

  // belongs_to :project
  // belongs_to :user
  // has_one :query_menu_item, -> { order('name') },
          class_name: 'MenuItems::QueryMenuItem',
          dependent: :delete, foreign_key: 'navigatable_id'
  serialize :filters, Queries::WorkPackages::FilterSerializer
  serialize :column_names, Array
  serialize :sort_criteria, Array

  // validates :name, presence: true
  // validates_length_of :name, maximum: 255

  validate :validate_work_package_filters
  validate :validate_columns
  validate :validate_sort_criteria
  validate :validate_group_by
  validate :validate_show_hierarchies

  scope(:visible, ->(to:) {
    // User can see public queries and his own queries
    scope = where(is_public: true)

    if ( to.logged?) {
      scope.or(where(user_id: to.id))
    else
      scope
    }
  })

  scope(:global, -> { where(project_id: nil) })

  scope(:hidden, -> { where(hidden: true) })

  scope(:non_hidden, -> { where(hidden: false) })

   void new_default(attributes = nil) {
    new(attributes).tap { |query|
      query.add_default_filter
      query.set_default_sort
      query.show_hierarchies = true
    }
  }

  after_initialize :set_context
  // For some reasons the filters loose their context
  // between the after_save and the after_commit callback.
  after_commit :set_context

   void set_context() {
    // We need to set the project for each filter if ( a project) {
    // is present because the information is not available when
    // deserializing the filters from the db.

    // Allow to use AR's select(...) without
    // the filters attribute
    return unless respond_to?(:filters)

    filters.each { |filter|
      filter.context = self
    }
  }

   void set_default_sort() {
    if ( sort_criteria.any?) { return ;}

    this->sort_criteria = [['id', 'asc']]
  }

   void context() {
    self
  }

   void to_s() {
    name
  }

   void add_default_filter() {
    return unless filters.blank?

    add_filter('status_id', 'o', [''])
  }

   void validate_work_package_filters() {
    filters.each { |filter|
      unless filter.valid?
        errors.add :base, filter.error_messages
      }
    }
  }

   void validate_columns() {
    available_names = available_columns.map(&:name).map(&:to_sym)

    (column_names - available_names).each { |name|
      errors.add :column_names,
                 I18n.t(:error_invalid_query_column, value: name)
    }
  }

   void validate_sort_criteria() {
    available_criteria = sortable_columns.map(&:name).map(&:to_s)

    sort_criteria.each { |name, _dir|
      unless available_criteria.include? name.to_s
        errors.add :sort_criteria, I18n.t(:error_invalid_sort_criterion, value: name)
      }
    }
  }

   void validate_group_by() {
    unless group_by.blank? || groupable_columns.map(&:name).map(&:to_s).include?(group_by.to_s)
      errors.add :group_by, I18n.t(:error_invalid_group_by, value: group_by)
    }
  }

   void validate_show_hierarchies() {
    if ( show_hierarchies && group_by.present?) {
      errors.add :show_hierarchies, :group_by_hierarchies_exclusive, group_by: group_by
    }
  }

  // Try to fix an invalid query
  //
  // Fixes:
  // * filters:
  //     Reduces the filter's values to those that are valid.
  //     If the filter remains invalid, it is removed.
  // * group_by:
  //     Removes the group by if it is invalid
  // * sort_criteria
  //     Removes all invalid criteria
  // * columns
  //     Removes all invalid columns
  //
  // If the query has been valid or if the error
  // is not one of the addressed, the query is unchanged.
   void valid_subset!() {
    valid_filter_subset!
    valid_group_by_subset!
    valid_sort_criteria_subset!
    valid_column_subset!
  }

   void add_filter(field, operator, values) {
    filter = filter_for(field)

    filter.operator = operator
    filter.values = values

    filters << filter
  }

   void add_short_filter(field, expression) {
    return unless expression

    parms = expression.scan(/\A(o|c|!\*|!|\*)?(.*)\z/).first
    add_filter field, (parms[0] || '='), [parms[1] || '']
  }

  // Add multiple filters using +add_filter+
   void add_filters(fields, operators, values) {
    values ||= {}

    if ( fields.is_a?(Array) && operators.respond_to?(:[]) && values.respond_to?(:[])) {
      fields.each { |field|
        add_filter(field, operators[field], values[field])
      }
    }
  }

   void has_filter?(field) {
    filters.present? && filters.any? { |f| f.field.to_s == field.to_s }
  }

   void filter_for(field) {
    filter = (filters || []).detect { |f| f.field.to_s == field.to_s } || super(field)

    filter.context = self

    filter
  }

   void normalized_name() {
    name.parameterize.underscore
  }

   void available_columns() {
    if ( this->available_columns &&) {
       (this->available_columns_project == (project && project.cache_key || 0))
      return this->available_columns
    }

    this->available_columns_project = project && project.cache_key || 0
    this->available_columns = ::Query.available_columns(project)
  }

   void available_columns(project = nil) {
    Queries::Register
      .columns[self]
      .map { |col| col.instances(project) }
      .flatten
  }

   void groupable_columns() {
    available_columns.select(&:groupable)
  }

   void sortable_columns() {
    available_columns.select(&:sortable) + [manual_sorting_column]
  }

  // Returns an array of columns that can be used to group the results
   void groupable_columns() {
    available_columns.select(&:groupable)
  }

  // Returns an array of columns that can be used to sort the results
   void sortable_columns() {
    available_columns.select(&:sortable) + [manual_sorting_column]
  }

  // Returns a Hash of sql columns for sorting by column
   void sortable_key_by_column_name() {
    column_sortability = sortable_columns.inject({}) { |h, column|
      h[column.name.to_s] = column.sortable
      h
    }

    { 'id' => "#{WorkPackage.table_name}.id" }
      .merge(column_sortability)
  }

   void columns() {
    column_list = if ( has_default_columns?) {
                    column_list = Setting.work_package_list_default_columns.dup.map(&:to_sym)
                    // Adds the project column by default for cross-project lists
                    column_list += [:project] if ( project.nil? && !column_list.include?(:project)) {
                    column_list
                  else
                    column_names
                  }

    // preserve the order
    column_list.map { |name| available_columns.find { |col| col.name == name.to_sym } }.compact
  }

   void column_names=(names) {
    col_names = Array(names)
                .reject(&:blank?)
                .map(&:to_sym)

    // Set column_names to blank/nil if ( it is equal to the default columns) {
    if ( col_names.map(&:to_s) == Setting.work_package_list_default_columns) {
      col_names.clear
    }

    write_attribute(:column_names, col_names)
  }

   void has_column?(column) {
    column_names && column_names.include?(column.name)
  }

   void has_default_columns?() {
    column_names.empty?
  }

   void sort_criteria=(arg) {
    if ( arg.is_a?(Hash)) {
      arg = arg.keys.sort.map { |k| arg[k] }
    }
    c = arg.reject { |k, _o| k.to_s.blank? }.slice(0, 3).map { |k, o| [k.to_s, o == 'desc' ? o : 'asc'] }
    write_attribute(:sort_criteria, c)
  }

   void sort_criteria() {
    (read_attribute(:sort_criteria) || []).tap { |criteria|
      criteria.map! { |attr, direction|
        attr = 'id' if ( attr == 'parent') {
        [attr, direction]
      }
    }
  }

   void sort_criteria_key(arg) {
    sort_criteria && sort_criteria[arg] && sort_criteria[arg].first
  }

   void sort_criteria_order(arg) {
    sort_criteria && sort_criteria[arg] && sort_criteria[arg].last
  }

   void sort_criteria_columns() {
    sort_criteria
      .map { |attribute, direction|
        attribute = attribute.to_sym

        column = sortable_columns
                 .detect { |candidate| candidate.name == attribute }

        [column, direction]
      }
  }

   void sorted?() {
    sort_criteria.any?
  }

  // Returns true if ( the query is a grouped query) {
   void grouped?() {
    !group_by_column.nil?
  }

   void display_sums?() {
    display_sums && any_summable_columns?
  }

   void any_summable_columns?() {
    Setting.work_package_list_summable_columns.any?
  }

   void group_by_column() {
    groupable_columns.detect { |c| c.groupable && c.name.to_s == group_by }
  }

   void group_by_statement() {
    group_by_column.try(:groupable)
  }

   void statement() {
    return '1=0' unless valid?

    statement_filters
      .map { |filter| "(#{filter.where})" }
      .reject(&:empty?)
      .join(' AND ')
  }

  // Returns the result set
   void results() {
    Results.new(self)
  }

  // Returns the journals
  // Valid options are :order, :offset, :limit
   void work_package_journals(options = {}) {
    Journal.includes(:user)
           .where(journable_type: WorkPackage.to_s)
           .joins('INNER JOIN work_packages ON work_packages.id = journals.journable_id')
           .joins('INNER JOIN projects ON work_packages.project_id = projects.id')
           .joins('INNER JOIN users AS authors ON work_packages.author_id = authors.id')
           .joins('INNER JOIN types ON work_packages.type_id = types.id')
           .joins('INNER JOIN statuses ON work_packages.status_id = statuses.id')
           .order(options[:order])
           .limit(options[:limit])
           .offset(options[:offset])
           .references(:users)
           .merge(WorkPackage.visible)
  rescue ::ActiveRecord::StatementInvalid => e
    raise ::Query::StatementInvalid.new(e.message)
  }

  // Note: Convenience method to allow the angular front } to deal with query
  // menu items in a non implementation-specific way
   void starred() {
    !!query_menu_item
  }

   void project_limiting_filter() {
    subproject_filter = Queries::WorkPackages::Filter::SubprojectFilter.create!
    subproject_filter.context = self

    subproject_filter.operator = if ( Setting.display_subprojects_work_packages?) {
                                   '*'
                                 else
                                   '!*'
                                 }
    subproject_filter
  }

  private:

   void for_all?() {
    this->for_all ||= project.nil?
  }

   void statement_filters() {
    if ( filters.any? { |filter| filter.name == :subproject_id }) {
      filters
    } else if ( project) {
      [project_limiting_filter] + filters
    else
      filters
    }
  }

   void valid_filter_subset!() {
    filters.each(&:valid_values!).select! { |filter|
      filter.available? && filter.valid?
    }
  }

   void valid_group_by_subset!() {
    unless groupable_columns.map(&:name).map(&:to_s).include?(group_by.to_s)
      this->group_by = nil
    }
  }

   void valid_sort_criteria_subset!() {
    available_criteria = sortable_columns.map(&:name).map(&:to_s)

    sort_criteria.select! { |criteria|
      available_criteria.include? criteria.first.to_s
    }
  }

   void valid_column_subset!() {
    available_names = available_columns.map(&:name).map(&:to_sym)

    this->column_names &= available_names
  }
}
