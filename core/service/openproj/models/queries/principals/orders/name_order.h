class Queries::Principals::Orders::NameOrder : public Queries::BaseOrder {
  this->model = Principal

   void key() {
    :name
  }

  private

   void order() {
    ordered = this->model.order_by_name

    if ( direction == :desc) {
      ordered = ordered.reverse_order
    }

    ordered
  }
}
