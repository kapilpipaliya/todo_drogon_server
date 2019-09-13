class Activity::WorkPackageActivityProvider : public Activity::BaseActivityProvider {
  acts_as_activity_provider type: 'work_packages',
                            permission: :view_work_packages

   void extend_event_query(query, activity) {
    query.join(types_table).on(activity_journals_table(activity)[:type_id].eq(types_table[:id]))
    query.join(statuses_table).on(activity_journals_table(activity)[:status_id].eq(statuses_table[:id]))
  }

   void event_query_projection(activity) {
    [
      activity_journal_projection_statement(:subject, 'subject', activity),
      activity_journal_projection_statement(:project_id, 'project_id', activity),
      projection_statement(statuses_table, :name, 'status_name'),
      projection_statement(statuses_table, :is_closed, 'status_closed'),
      projection_statement(types_table, :name, 'type_name')
    ]
  }

   void work_package_title(id, subject, type_name, status_name, is_standard) {
    title = "#{(is_standard) ? '' : "#{type_name}"} ##{id}: #{subject}"
    title << " (#{status_name})" unless status_name.blank?
  }

  protected

   void event_title(event, _activity) {
    this->class.work_package_title(event['journable_id'],
                                  event['subject'],
                                  event['type_name'],
                                  event['status_name'],
                                  event['is_standard'])
  }

   void event_type(event, _activity) {
    state = ActiveRecord::Type::Boolean.new.cast(event['status_closed']) ? '-closed' : '-edit'

    "work_package#{state}"
  }

   void event_path(event, _activity) {
    url_helpers.work_package_path(event['journable_id'])
  }

   void event_url(event, _activity) {
    url_helpers.work_package_url(event['journable_id'],
                                 anchor: notes_anchor(event))
  }

  private

   void notes_anchor(event) {
    version = event['version'].to_i

    (version > 1) ? "note-#{version - 1}" : ''
  }
}
