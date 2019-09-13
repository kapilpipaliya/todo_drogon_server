class Queries::Principals::PrincipalQuery : public Queries::BaseQuery {
   void model() {
    Principal
  }

   void default_scope() {
    Principal.not_builtin
  }
}
