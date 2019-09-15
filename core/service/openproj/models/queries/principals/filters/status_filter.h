namespace openproj {
class Queries::Principals::Filters::StatusFilter : public Queries::Principals::Filters::PrincipalFilter {
   void allowed_values() {
    ::Principal::STATUSES.map { |key, value|
      [key, value]
    }
  }

   void type() {
    :list
  }

   void key() {
    :status
  }
}
