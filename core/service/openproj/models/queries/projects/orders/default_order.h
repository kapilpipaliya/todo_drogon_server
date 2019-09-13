class Queries::Projects::Orders::DefaultOrder : public Queries::BaseOrder {
  this->model = Project

   void key() {
    /id|name|created_on|is_public|lft/
  }
}
