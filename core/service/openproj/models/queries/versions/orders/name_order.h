class Queries::Versions::Orders::NameOrder : public Queries::BaseOrder {
  this->model = Version

   void key() {
    :name
  }

  private

   void order() {
    ordered = Version.order_by_name

    if ( direction == :desc) {
      ordered = ordered.reverse_order
    }

    ordered
  }
}
