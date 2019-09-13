class Journal::ChangesetJournal : public Journal::BaseJournal {
  this->table_name = 'changeset_journals'
}

::ChangesetJournal = Journal::ChangesetJournal
