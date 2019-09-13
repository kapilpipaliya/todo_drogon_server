class Queries::Users::UserQuery : public Queries::BaseQuery {
   void model() {
    User
  }

   void default_scope() {
    User.not_builtin
  }
}
