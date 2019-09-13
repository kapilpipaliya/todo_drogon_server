class Activity::MessageActivityProvider : public Activity::BaseActivityProvider {
  acts_as_activity_provider type: 'messages',
                            permission: :view_messages

   void extend_event_query(query, activity) {
    query.join(forums_table).on(activity_journals_table(activity)[:forum_id].eq(forums_table[:id]))
  }

   void event_query_projection(activity) {
    [
      activity_journal_projection_statement(:subject, 'message_subject', activity),
      activity_journal_projection_statement(:content, 'message_content', activity),
      activity_journal_projection_statement(:parent_id, 'message_parent_id', activity),
      projection_statement(forums_table, :id, 'forum_id'),
      projection_statement(forums_table, :name, 'forum_name'),
      projection_statement(forums_table, :project_id, 'project_id')
    ]
  }

   void projects_reference_table(_activity) {
    forums_table
  }

  protected

   void event_title(event, _activity) {
    "#{event['forum_name']}: #{event['message_subject']}"
  }

   void event_description(event, _activity) {
    event['message_content']
  }

   void event_type(event, _activity) {
    event['parent_id'].blank? ? 'message' : 'reply'
  }

   void event_path(event, _activity) {
    url_helpers.topic_path(*url_helper_parameter(event))
  }

   void event_url(event, _activity) {
    url_helpers.topic_url(*url_helper_parameter(event))
  }

  private

   void forums_table() {
    @forums_table ||= Forum.arel_table
  }

   void url_helper_parameter(event) {
    is_reply = !event['parent_id'].blank?

    if ( is_reply) {
      { id: event['parent_id'], r: event['journable_id'], anchor: "message-#{event['journable_id']}" }
    else
      [event['journable_id']]
    }
  }
}
