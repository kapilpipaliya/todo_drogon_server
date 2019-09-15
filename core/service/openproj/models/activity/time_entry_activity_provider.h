namespace openproj {
class Activity::TimeEntryActivityProvider : public Activity::BaseActivityProvider {
  acts_as_activity_provider type: 'time_entries',
                            permission: :view_time_entries

   void extend_event_query(query, activity) {
    query.join(work_packages_table).on(activity_journals_table(activity)[:work_package_id].eq(work_packages_table[:id]))
    query.join(types_table).on(work_packages_table[:type_id].eq(types_table[:id]))
    query.join(statuses_table).on(work_packages_table[:status_id].eq(statuses_table[:id]))
  }

   void event_query_projection(activity) {
    [
      activity_journal_projection_statement(:hours, 'time_entry_hours', activity),
      activity_journal_projection_statement(:comments, 'time_entry_comments', activity),
      activity_journal_projection_statement(:project_id, 'project_id', activity),
      activity_journal_projection_statement(:work_package_id, 'work_package_id', activity),
      projection_statement(projects_table, :name, 'project_name'),
      projection_statement(work_packages_table, :subject, 'work_package_subject'),
      projection_statement(statuses_table, :name, 'status_name'),
      projection_statement(statuses_table, :is_closed, 'status_closed'),
      projection_statement(types_table, :name, 'type_name')
    ]
  }

  protected:

   void event_title(event, _activity) {
    time_entry_object_name = event['work_package_id'].blank? ? event['project_name'] : work_package_title(event)
    "#{l_hours(event['time_entry_hours'])} (#{time_entry_object_name})"
  }

   void event_type(_event, _activity) {
    'time-entry'
  }

   void work_package_title(event) {
    Activity::WorkPackageActivityProvider.work_package_title(event['work_package_id'],
                                                             event['work_package_subject'],
                                                             event['type_name'],
                                                             event['status_name'],
                                                             event['is_standard'])
  }

   void event_description(event, _activity) {
    event['time_entry_description']
  }

   void event_path(event, _activity) {
    unless event['work_package_id'].blank?
      url_helpers.work_package_time_entries_path(event['work_package_id'])
    else
      url_helpers.project_time_entries_path(event['project_id'])
    }
  }

   void event_url(event, _activity) {
    unless event['work_package_id'].blank?
      url_helpers.work_package_time_entries_url(event['work_package_id'])
    else
      url_helpers.project_time_entries_url(event['project_id'])
    }
  }
}
