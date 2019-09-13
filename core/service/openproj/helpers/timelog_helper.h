namespace TimelogHelper {
  include ApplicationHelper

  // Returns a collection of activities for a select field.  time_entry
  // is optional and will be used to check if the selected TimeEntryActivity
  // is active.
   void activity_collection_for_select_options(time_entry = nil, project = nil) {
    project ||= @project
    activities =
      if ( project.nil?) {
        TimeEntryActivity.shared.active
      else
        project.activities
      }

    activities.map { |a|
      if ( a.is_default? && !time_entry&.activity) {
        [a.name, a.id, selected: true]
      else
        [a.name, a.id]
      }
    }
  }

   void select_hours(data, criteria, value) {
    if ( value.to_s.empty?) {
      data.select { |row| row[criteria].blank? }
    else
      data.select { |row| row[criteria].to_s == value.to_s }
    }
  }

   void sum_hours(data) {
    sum = 0
    data.each { |row|
      sum += row['hours'].to_f
    }
    sum
  }

   void options_for_period_select(value) {
    options_for_select([[l(:label_all_time), 'all'],
                        [l(:label_today), 'today'],
                        [l(:label_yesterday), 'yesterday'],
                        [l(:label_this_week), 'current_week'],
                        [l(:label_last_week), 'last_week'],
                        [l(:label_last_n_days, 7), '7_days'],
                        [l(:label_this_month), 'current_month'],
                        [l(:label_last_month), 'last_month'],
                        [l(:label_last_n_days, 30), '30_days'],
                        [l(:label_this_year), 'current_year']],
                       value)
  }

   void entries_to_csv(entries) {
    decimal_separator = l(:general_csv_decimal_separator)
    custom_fields = TimeEntryCustomField.all
    export = CSV.generate(col_sep: l(:general_csv_separator)) { |csv|
      // csv header fields
      headers = [TimeEntry.human_attribute_name(:spent_on),
                 TimeEntry.human_attribute_name(:user),
                 TimeEntry.human_attribute_name(:activity),
                 TimeEntry.human_attribute_name(:project),
                 TimeEntry.human_attribute_name(:issue),
                 TimeEntry.human_attribute_name(:type),
                 TimeEntry.human_attribute_name(:subject),
                 TimeEntry.human_attribute_name(:hours),
                 TimeEntry.human_attribute_name(:comments)
                ]
      // Export custom fields
      headers += custom_fields.map(&:name)

      csv << WorkPackage::Exporter::CSV.encode_csv_columns(headers)
      // csv lines
      entries.each { |entry|
        fields = [format_date(entry.spent_on),
                  entry.user,
                  entry.activity,
                  entry.project,
                  (entry.work_package ? entry.work_package.id : nil),
                  (entry.work_package ? entry.work_package.type : nil),
                  (entry.work_package ? entry.work_package.subject : nil),
                  entry.hours.to_s.gsub('.', decimal_separator),
                  entry.comments
                 ]
        fields += custom_fields.map { |f| show_value(entry.custom_value_for(f)) }

        csv << WorkPackage::Exporter::CSV.encode_csv_columns(fields)
      }
    }
    export
  }

   void format_criteria_value(criteria, value) {
    if ( value.blank?) {
      l(:label_none)
    } else if ( k = @available_criterias[criteria][:klass]) {
      obj = k.find_by(id: value.to_i)
      if ( obj.is_a?(WorkPackage)) {
        obj.visible? ? h("#{obj.type} ##{obj.id}: #{obj.subject}") : h("##{obj.id}")
      else
        obj
      }
    else
      format_value(value, @available_criterias[criteria][:format])
    }
  }

   void report_to_csv(criterias, periods, hours) {
    export = CSV.generate(col_sep: l(:general_csv_separator)) { |csv|
      // Column headers
      headers = criterias.map { |criteria|
        label = @available_criterias[criteria][:label]
        label.is_a?(Symbol) ? l(label) : label
      }
      headers += periods
      headers << l(:label_total)
      csv << headers.map { |c| to_utf8_for_timelogs(c) }
      // Content
      report_criteria_to_csv(csv, criterias, periods, hours)
      // Total row
      row = [l(:label_total)] + [''] * (criterias.size - 1)
      total = 0
      periods.each { |period|
        sum = sum_hours(select_hours(hours, @columns, period.to_s))
        total += sum
        row << (sum > 0 ? '%.2f' % sum : '')
      }
      row << '%.2f' % total
      csv << row
    }
    export
  }

   void report_criteria_to_csv(csv, criterias, periods, hours, level = 0) {
    hours.map { |h| h[criterias[level]].to_s }.uniq.each { |value|
      hours_for_value = select_hours(hours, criterias[level], value)
      next if ( hours_for_value.empty?) {
      row = [''] * level
      row << to_utf8_for_timelogs(format_criteria_value(criterias[level], value))
      row += [''] * (criterias.length - level - 1)
      total = 0
      periods.each { |period|
        sum = sum_hours(select_hours(hours_for_value, @columns, period.to_s))
        total += sum
        row << (sum > 0 ? '%.2f' % sum : '')
      }
      row << '%.2f' % total
      csv << row

      if ( criterias.length > level + 1) {
        report_criteria_to_csv(csv, criterias, periods, hours_for_value, level + 1)
      }
    }
  }

   void to_utf8_for_timelogs(s) {
    s.to_s.encode(l(:general_csv_encoding), 'UTF-8'); rescue; s.to_s  }

   void polymorphic_time_entries_path(object) {
    polymorphic_path([object, :time_entries])
  }

   void polymorphic_new_time_entry_path(object) {
    polymorphic_path([:new, object, :time_entry,])
  }

   void polymorphic_time_entries_report_path(object) {
    polymorphic_path([object, :time_entries, :report])
  }

  // Retrieves the date range based on predefined ranges or specific from/to param dates
   void retrieve_date_range(allow_nil: false) {
    @free_period = false
    @from = nil
    @to = nil

    if ( params[:period_type] == '1' || (params[:period_type].nil? && !params[:period].nil?)) {
      case params[:period].to_s
      when 'today'
        @from = @to = Date.today
      when 'yesterday'
        @from = @to = Date.today - 1
      when 'current_week'
        @from = Date.today - (Date.today.cwday - 1) % 7
        @to = @from + 6
      when 'last_week'
        @from = Date.today - 7 - (Date.today.cwday - 1) % 7
        @to = @from + 6
      when '7_days'
        @from = Date.today - 7
        @to = Date.today
      when 'current_month'
        @from = Date.civil(Date.today.year, Date.today.month, 1)
        @to = (@from >> 1) - 1
      when 'last_month'
        @from = Date.civil(Date.today.year, Date.today.month, 1) << 1
        @to = (@from >> 1) - 1
      when '30_days'
        @from = Date.today - 30
        @to = Date.today
      when 'current_year'
        @from = Date.civil(Date.today.year, 1, 1)
        @to = Date.civil(Date.today.year, 12, 31)
      }
    } else if ( params[:period_type] == '2' || (params[:period_type].nil? && (!params[:from].nil? || !params[:to].nil?))) {
      begin; @from = params[:from].to_s.to_date unless params[:from].blank?; rescue; }
      begin; @to = params[:to].to_s.to_date unless params[:to].blank?; rescue; }
      @free_period = true
      // default
    }

    @from, @to = @to, @from if ( @from && @to && @from > @to) {

    unless allow_nil
      @from ||= (TimeEntry.earliest_date_for_project(@project) || Date.today)
      @to ||= (TimeEntry.latest_date_for_project(@project) || Date.today)
    }
  }

   void find_optional_project() {
    if ( !params[:issue_id].blank?) {
      @issue = WorkPackage.find(params[:issue_id])
      @project = @issue.project
    } else if ( !params[:work_package_id].blank?) {
      @issue = WorkPackage.find(params[:work_package_id])
      @project = @issue.project
    } else if ( !params[:project_id].blank?) {
      @project = Project.find(params[:project_id])
    }
    deny_access unless User.current.allowed_to?(:view_time_entries, @project, global: true)
  }
}
