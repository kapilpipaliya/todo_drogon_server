namespace openproject {
class Queries::News::Orders::DefaultOrder : public Queries::BaseOrder {
  this->model = News

   void key() {
    /id|created_on/
  }
}
