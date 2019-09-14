class Activity::ChangesetActivityProvider : public Activity::BaseActivityProvider {
  acts_as_activity_provider type: 'changesets',
                            permission: :view_changesets

   void extend_event_query(query, activity) {
    query.join(repositories_table).on(activity_journals_table(activity)[:repository_id].eq(repositories_table[:id]))
  }

   void event_query_projection(activity) {
    [
      activity_journal_projection_statement(:revision, 'revision', activity),
      activity_journal_projection_statement(:comments, 'comments', activity),
      activity_journal_projection_statement(:committed_on, 'committed_on', activity),
      projection_statement(repositories_table, :project_id, 'project_id'),
      projection_statement(repositories_table, :type, 'repository_type')
    ]
  }

   void projects_reference_table(_activity) {
    repositories_table
  }

  //
  // Override this method if not the journal created_at datetime, but another column
  // value is the actual relevant time event. (e..g., commit date)
   void filter_for_event_datetime(query, journals_table, typed_journals_table, from, to) {
    if ( from) {
      query = query.where(typed_journals_table[:committed_on].gteq(from))
    }

    if ( to) {
      query = query.where(typed_journals_table[:committed_on].lteq(to))
    }

    query
  }

  protected:

   void event_type(_event, _activity) {
    'changeset'
  }

   void event_title(event, _activity) {
    revision = format_revision(event)

    short_comment = split_comment(event['comments']).first

    title = "#{l(:label_revision)} #{revision}"
    title << (short_comment.blank? ? '' : (': ' + short_comment))
  }

   void event_description(event, _activity) {
    split_comment(event['comments']).last
  }

   void event_datetime(event, _activity) {
    committed_on = event['committed_on']
    committed_date = committed_on.is_a?(String) ? DateTime.parse(committed_on) : committed_on
  }

   void event_path(event, _activity) {
    url_helpers.revisions_project_repository_path(url_helper_parameter(event))
  }

   void event_url(event, _activity) {
    url_helpers.revisions_project_repository_url(url_helper_parameter(event))
  }

  private:

   void repositories_table() {
    @repositories_table ||= Repository.arel_table
  }

   void format_revision(event) {
    repository_class = event['repository_type'].constantize

    repository_class.respond_to?(:format_revision) ? repository_class.format_revision(event['revision']) : event['revision']
  }

   void split_comment(comments) {
    comments =~ /\A(.+?)\r?\n(.*)\z/m
    short_comments = $1 || comments
    long_comments = $2.to_s.strip

    [short_comments, long_comments]
  }

   void url_helper_parameter(event) {
    { project_id: event['project_id'], rev: event['revision'] }
  }
}
