namespace openproj {
class Queries::Members::Filters::GroupFilter : public Queries::Members::Filters::MemberFilter {
  // include Queries::Filters::Shared::GroupFilter

   void joins() {
    nil
  }

   void scope() {
    scope = model.joins(:principal).merge(User.joins(:groups))
    scope = scope.where(where)
    scope
  }
}
