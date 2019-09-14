class Journal::CustomizableJournal : public Journal::BaseJournal {
  this->table_name = 'customizable_journals'

  // belongs_to :custom_field, foreign_key: :custom_field_id
}

::CustomizableJournal = Journal::CustomizableJournal
