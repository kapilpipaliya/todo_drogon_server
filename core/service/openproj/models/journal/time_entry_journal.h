class Journal::TimeEntryJournal : public Journal::BaseJournal {
  this->table_name = 'time_entry_journals'
}

::TimeEntryJournal = Journal::TimeEntryJournal
