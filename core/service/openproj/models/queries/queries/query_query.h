class Queries::Queries::QueryQuery : public Queries::BaseQuery {
   void model() {
    Query
  }

   void default_scope() {
    Query.visible(to: user)
  }
}
