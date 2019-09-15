namespace openproj {
class Queries::Principals::Filters::TypeFilter : public Queries::Principals::Filters::PrincipalFilter {
   void allowed_values() {
    [[Group.to_s, Group.to_s],
     [User.to_s, User.to_s]]
  }

   void type() {
    :list
  }

   void key() {
    :type
  }

   void scope() {
    if ( operator == '=') {
      Principal.where(type: values)
    else
      Principal.where.not(type: values)
    }
  }
}
