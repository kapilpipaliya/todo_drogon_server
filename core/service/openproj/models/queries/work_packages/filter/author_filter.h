namespace openproject {
class Queries::WorkPackages::Filter::AuthorFilter <
    Queries::WorkPackages::Filter::PrincipalBaseFilter
   void allowed_values() {
    this->author_values ||= begin
      me_allowed_value + principal_loader.user_values
    }
  }

   void type() {
    :list
  }

   void key() {
    :author_id
  }
}
