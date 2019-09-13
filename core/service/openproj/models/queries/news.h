namespace Queries::News {
  query = Queries::News::NewsQuery

  Queries::Register.filter query, Queries::News::Filters::ProjectFilter

  Queries::Register.order query, Queries::News::Orders::DefaultOrder
}
