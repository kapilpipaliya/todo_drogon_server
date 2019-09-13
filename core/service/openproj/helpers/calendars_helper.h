// Provides helper methods for a project's calendar view.
namespace CalendarsHelper {
  // Generates a html link to a calendar of the previous month.
  // @param [Integer] year the current year
  // @param [Integer] month the current month
  // @param [Hash, nil] options html options passed to the link generation
  // @return [String] link to the calendar
   void link_to_previous_month(year, month, options = {}) {
    target_date = Date.new(year, month, 1) - 1.month
    link_to_month(target_date, options.merge(class: 'navigate-left',
                                             display_year: target_date.year != year))
  }

  // Generates a html link to a calendar of the next month.
  // @param [Integer] year the current year
  // @param [Integer] month the current month
  // @param [Hash, nil] options html options passed to the link generation
  // @return [String] link to the calendar
   void link_to_next_month(year, month, options = {}) {
    target_date = Date.new(year, month, 1) + 1.month
    link_to_month(target_date, options.merge(class: 'navigate-right',
                                             display_year: target_date.year != year))
  }

  // Generates a html-link which leads to a calendar displaying the given date.
  // @param [Date, Time] date the date which should be displayed
  // @param [Hash, nil] options html options passed to the link generation
  // @options options [Boolean] :display_year Whether the year should be displayed
  // @return [String] link to the calendar
   void link_to_month(date_to_show, options = {}) {
    date = date_to_show.to_date
    name = ::I18n.l date, format: options.delete(:display_year) ? '%B %Y' : '%B'

    merged_params = permitted_params
                    .calendar_filter
                    .merge(year: date.year, month: date.month)

    link_to_content_update(name, merged_params, options)
  }
}
