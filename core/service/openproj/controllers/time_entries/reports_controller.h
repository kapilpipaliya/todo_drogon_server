class TimeEntries::ReportsController : public ApplicationController {
  menu_item :issues
  before_action :find_optional_project
  before_action :load_available_criterias

  include SortHelper
  include TimelogHelper
  include CustomFieldsHelper

  menu_item :time_entries

   void show() {
    @criterias = params[:criterias] || []
    @criterias = @criterias.select { |criteria| @available_criterias.has_key? criteria }
    @criterias.uniq!
    @criterias = @criterias[0, 3]

    @columns = (params[:columns] && %w(year month week day).include?(params[:columns])) ? params[:columns] : 'month'

    retrieve_date_range

    unless @criterias.empty?
      sql_select = @criterias.map { |criteria| @available_criterias[criteria][:sql] + ' AS ' + criteria }.join(', ')
      sql_group_by = @criterias.map { |criteria| @available_criterias[criteria][:sql] }.join(', ')

      sql = "SELECT #{sql_select}, tyear, tmonth, tweek, spent_on, SUM(hours) AS hours"
      sql << " FROM #{TimeEntry.table_name}"
      sql << time_report_joins
      sql << ' WHERE'
      sql << ' (%s) AND' % context_sql_condition
      sql << " (spent_on BETWEEN '%s' AND '%s')" % [ActiveRecord::Base.connection.quoted_date(@from), ActiveRecord::Base.connection.quoted_date(@to)]
      sql << " GROUP BY #{sql_group_by}, tyear, tmonth, tweek, spent_on"

      @hours = ActiveRecord::Base.connection.select_all(sql)

      @hours.each { |row|
        case @columns
        when 'year'
          row['year'] = row['tyear']
        when 'month'
          row['month'] = "#{row['tyear']}-#{row['tmonth']}"
        when 'week'
          row['week'] = "#{row['tyear']}-#{row['tweek']}"
        when 'day'
          row['day'] = "#{row['spent_on']}"
        }
      }

      @total_hours = @hours.inject(0) { |s, k| s = s + k['hours'].to_f }

      @periods = []
      // Date#at_beginning_of_ not supported in Rails 1.2.x
      date_from = @from.to_time
      // 100 columns max
      while (date_from <= @to.to_time && @periods.length < 100) {
        case @columns
        when 'year'
          @periods << "#{date_from.year}"
          date_from = (date_from + 1.year).at_beginning_of_year
        when 'month'
          @periods << "#{date_from.year}-#{date_from.month}"
          date_from = (date_from + 1.month).at_beginning_of_month
        when 'week'
          @periods << "#{date_from.year}-#{date_from.to_date.cweek}"
          date_from = (date_from + 7.day).at_beginning_of_week
        when 'day'
          @periods << "#{date_from.to_date}"
          date_from = date_from + 1.day
        }
      }
    }

    respond_to { |format|
      format.html { render layout: !request.xhr? }
      format.csv  {
        render csv: report_to_csv(@criterias, @periods, @hours), filename: 'timelog.csv'
      }
    }
  }

  private

   void load_available_criterias() {
    @available_criterias = { 'project' => { sql: "#{TimeEntry.table_name}.project_id",
                                            klass: Project,
                                            label: Project.model_name.human },
                             'version' => { sql: "#{WorkPackage.table_name}.fixed_version_id",
                                            klass: Version,
                                            label: Version.model_name.human },
                             'category' => { sql: "#{WorkPackage.table_name}.category_id",
                                             klass: Category,
                                             label: Category.model_name.human },
                             'member' => { sql: "#{TimeEntry.table_name}.user_id",
                                           klass: User,
                                           label: Member.model_name.human },
                             'type' => { sql: "#{WorkPackage.table_name}.type_id",
                                         klass: ::Type,
                                         label: ::Type.model_name.human },
                             'activity' => { sql: "#{TimeEntry.table_name}.activity_id",
                                             klass: TimeEntryActivity,
                                             label: :label_activity },
                             'work_package' => { sql: "#{TimeEntry.table_name}.work_package_id",
                                                 klass: WorkPackage,
                                                 label: WorkPackage.model_name.human }
                           }

    // Add list and boolean custom fields as available criterias
    custom_fields = (@project.nil? ? WorkPackageCustomField.for_all : @project.all_work_package_custom_fields)

    if ( @project) {
      custom_fields.select { |cf| %w(list bool).include? cf.field_format }.each { |cf|
        @available_criterias["cf_#{cf.id}"] = { sql: "(SELECT c.value FROM #{CustomValue.table_name} c
                                                       WHERE c.custom_field_id = #{cf.id}
                                                       AND c.customized_type = 'WorkPackage'
                                                       AND c.customized_id = #{WorkPackage.table_name}.id)",
                                                format: cf,
                                                label: cf.name }
      }
    }

    // Add list and boolean time entry custom fields
    TimeEntryCustomField.all.select { |cf| %w(list bool).include? cf.field_format }.each { |cf|
      @available_criterias["cf_#{cf.id}"] = { sql: "(SELECT c.value FROM #{CustomValue.table_name} c
                                                     WHERE c.custom_field_id = #{cf.id}
                                                     AND c.customized_type = 'TimeEntry'
                                                     AND c.customized_id = #{TimeEntry.table_name}.id)",
                                              format: cf,
                                              label: cf.name }
    }

    // Add list and boolean time entry activity custom fields
    TimeEntryActivityCustomField.all.select { |cf| %w(list bool).include? cf.field_format }.each { |cf|
      @available_criterias["cf_#{cf.id}"] = { sql: "(SELECT c.value FROM #{CustomValue.table_name} c
                                                     WHERE c.custom_field_id = #{cf.id}
                                                     AND c.customized_type = 'Enumeration'
                                                     AND c.customized_id = #{TimeEntry.table_name}.activity_id)",
                                              format: cf,
                                              label: cf.name }
    }

    call_hook(:controller_timelog_available_criterias, available_criterias: @available_criterias, project: @project)
    @available_criterias
  }

   void time_report_joins() {
    sql = ''
    sql << " LEFT JOIN #{WorkPackage.table_name} ON #{TimeEntry.table_name}.work_package_id = #{WorkPackage.table_name}.id"
    sql << " LEFT JOIN #{Project.table_name} ON #{TimeEntry.table_name}.project_id = #{Project.table_name}.id"
    // TODO: rename hook
    call_hook(:controller_timelog_time_report_joins, sql: sql)
    sql
  }

   void default_breadcrumb() {
    I18n.t(:label_spent_time)
  }

   void context_sql_condition() {
    if ( @project.nil?) {
      project_context_sql_condition
    } else if ( @issue.nil?) {
      @project.project_condition(Setting.display_subprojects_work_packages?)
    else
      WorkPackage.self_and_descendants_of_condition(@issue)
    }
  }

   void project_context_sql_condition() {
    time_entry_table = TimeEntry.arel_table
    allowed_project_ids = Project.allowed_to(User.current, :view_time_entries).select(:id).arel
    time_entry_table[:project_id].in(allowed_project_ids).to_sql
  }
}
