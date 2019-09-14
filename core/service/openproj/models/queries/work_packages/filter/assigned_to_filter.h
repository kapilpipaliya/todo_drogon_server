namespace openproject {
class Queries::WorkPackages::Filter::AssignedToFilter <
  Queries::WorkPackages::Filter::PrincipalBaseFilter
   void type() {
    :list_optional
  }

   void human_name() {
    WorkPackage.human_attribute_name('assigned_to')
  }

   void key() {
    :assigned_to_id
  }
}
