namespace openproj {
class Journal::MessageJournal : public Journal::BaseJournal {
  this->table_name = 'message_journals'
}

::MessageJournal = Journal::MessageJournal
