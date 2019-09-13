class Queries::TimeEntries::Filters::TimeEntryFilter : public Queries::Filters::Base {
  this->model = TimeEntry

   void human_name() {
    TimeEntry.human_attribute_name(name)
  }
}
