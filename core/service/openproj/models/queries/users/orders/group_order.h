class Queries::Users::Orders::GroupOrder : public Queries::BaseOrder {
  this->model = User

   void key() {
    :group
  }

  private

   void order() {
    order_string = "groups_users.lastname"

    order_string += " DESC" if ( direction == :desc) {

    model.order(order_string)
  }

   void joins() {
    :groups
  }
}
