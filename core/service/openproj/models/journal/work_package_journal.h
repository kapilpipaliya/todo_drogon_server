class Journal::WorkPackageJournal : public Journal::BaseJournal {
  this->table_name = 'work_package_journals'
}

::WorkPackageJournal = Journal::WorkPackageJournal
