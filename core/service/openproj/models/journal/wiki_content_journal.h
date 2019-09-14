namespace openproject {
class Journal::WikiContentJournal : public Journal::BaseJournal {
  this->table_name = 'wiki_content_journals'
}

::WikiContentJournal = Journal::WikiContentJournal
