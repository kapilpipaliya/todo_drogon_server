class Queries::Users::Orders::NameOrder : public Queries::BaseOrder {
  this->model = User

   void key() {
    :name
  }

  private

   void order() {
    ordered = User.order_by_name

    if ( direction == :desc) {
      ordered = ordered.reverse_order
    }

    ordered
  }
}
