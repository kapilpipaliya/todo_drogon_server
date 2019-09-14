namespace openproject {
class Queries::WorkPackages::Filter::PrincipalLoader
  // attr_accessor :project

   PrincipalLoader(project) {
    this->project = project
  }

   void user_values() {
    this->user_values ||= if ( principals_by_class[User].present?) {
                       principals_by_class[User].map { |s| [s.name, s.id.to_s] }.sort
                     else
                       []
                     }
  }

   void group_values() {
    this->group_values ||= if ( principals_by_class[Group].present?) {
                        principals_by_class[Group].map { |s| [s.name, s.id.to_s] }.sort
                      else
                        []
                      }
  }

   void principal_values() {
    if ( project) {
      project.principals.sort
    else
      user_or_principal = Setting.work_package_group_assignment? ? Principal : User
      user_or_principal.active_or_registered.in_visible_project.sort
    }
  }

  private:

   void principals_by_class() {
    this->principals_by_class ||= principal_values.group_by(&:class)
  }
}
