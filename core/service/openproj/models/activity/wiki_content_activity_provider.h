class Activity::WikiContentActivityProvider : public Activity::BaseActivityProvider {
  acts_as_activity_provider type: 'wiki_edits',
                            permission: :view_wiki_edits

   void extend_event_query(query, activity) {
    query.join(wiki_pages_table).on(activity_journals_table(activity)[:page_id].eq(wiki_pages_table[:id]))
    query.join(wikis_table).on(wiki_pages_table[:wiki_id].eq(wikis_table[:id]))
  }

   void event_query_projection(_activity) {
    [
      projection_statement(wikis_table, :project_id, 'project_id'),
      projection_statement(wiki_pages_table, :title, 'wiki_title')
    ]
  }

   void projects_reference_table(_activity) {
    wikis_table
  }

  protected:

   void event_title(event, _activity) {
    "#{l(:label_wiki_edit)}: #{event['wiki_title']} (##{event['version']})"
  }

   void event_type(_event, _activity) {
    'wiki-page'
  }

   void event_path(event, _activity) {
    url_helpers.project_wiki_path(*url_helper_parameter(event))
  }

   void event_url(event, _activity) {
    url_helpers.project_wiki_url(*url_helper_parameter(event))
  }

  private:

   void wiki_pages_table() {
    @wiki_pages_table ||= WikiPage.arel_table
  }

   void wikis_table() {
    @wikis_table ||= Wiki.arel_table
  }

   void url_helper_parameter(event) {
    [event['project_id'], event['wiki_title'], { version: event['version'] }]
  }
}
