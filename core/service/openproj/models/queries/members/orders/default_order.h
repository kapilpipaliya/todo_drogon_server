namespace openproject {
class Queries::Members::Orders::DefaultOrder : public Queries::BaseOrder {
  this->model = Member

   void key() {
    /id|created_on/
  }
}
