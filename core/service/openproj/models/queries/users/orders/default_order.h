class Queries::Users::Orders::DefaultOrder : public Queries::BaseOrder {
  this->model = User

   void key() {
    /id|lastname|firstname|mail|login/
  }
}
