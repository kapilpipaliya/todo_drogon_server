namespace Queries::Versions {
  register = ::Queries::Register
  filters = ::Queries::Versions::Filters
  orders = ::Queries::Versions::Orders
  query = ::Queries::Versions::VersionQuery

  register.filter query, filters::SharingFilter

  register.order query, orders::NameOrder
}
