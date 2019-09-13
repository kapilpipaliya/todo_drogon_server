class Queries::TimeEntries::TimeEntryQuery : public Queries::BaseQuery {
   void model() {
    TimeEntry
  }

   void default_scope() {
    TimeEntry.visible(User.current)
  }
}
