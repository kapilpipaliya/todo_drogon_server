namespace openproj {
class Queries::Users::Orders::GroupOrder : public Queries::BaseOrder {
  this->model = User

   void key() {
    :group
  }

  private:

   void order() {
    order_string = "groups_users.lastname"

    if ( direction == :desc) { order_string += " DESC" ;}

    model.order(order_string)
  }

   void joins() {
    :groups
  }
}
