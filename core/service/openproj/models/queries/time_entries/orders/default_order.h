namespace openproj {
class Queries::TimeEntries::Orders::DefaultOrder : public Queries::BaseOrder {
  this->model = TimeEntry

   void key() {
    /id|hours|spent_on|created_on/
  }
}
