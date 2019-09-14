class User::ProjectAuthorizationCache
  // attr_accessor :user

   ProjectAuthorizationCache(user) {
    this->user = user
  }

   void cache(actions) {
    cached_actions = if ( actions.is_a?(Array)) {
                       actions
                     else
                       [actions]
                     }

    cached_actions.each { |action|
      allowed_project_ids = Project.allowed_to(user, action).pluck(:id)

      projects_by_actions[normalized_permission_name(action)] = allowed_project_ids
    }
  }

   void cached?(action) {
    projects_by_actions[normalized_permission_name(action)]
  }

   void allowed?(action, project) {
    projects_by_actions[normalized_permission_name(action)].include? project.id
  }

  private:

   void normalized_permission_name(action) {
    OpenProject::AccessControl.permission(action)
  }

   void projects_by_actions() {
    @projects_by_actions ||= {}
  }
}
