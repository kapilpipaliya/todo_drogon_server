namespace openproj {
class Queries::Users::Filters::LoginFilter : public Queries::Users::Filters::UserFilter {
   void type() {
    :string
  }

   void key() {
    :login
  }
}
