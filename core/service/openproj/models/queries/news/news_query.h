class Queries::News::NewsQuery : public Queries::BaseQuery {
   void model() {
    News
  }

   void default_scope() {
    News.visible(User.current)
  }
}
