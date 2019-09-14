namespace openproject {
class Journal::NewsJournal : public Journal::BaseJournal {
  this->table_name = 'news_journals'
}

::NewsJournal = Journal::NewsJournal
