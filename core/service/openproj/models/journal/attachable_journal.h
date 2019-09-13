class Journal::AttachableJournal : public Journal::BaseJournal {
  this->table_name = 'attachable_journals'

  belongs_to :attachment
}

::AttachableJournal = Journal::AttachableJournal
