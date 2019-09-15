namespace openproj {
class User::ProjectRoleCache
  // attr_accessor :user

   ProjectRoleCache(user) {
    this->user = user
  }

   void fetch(project) {
    cache[project] ||= roles(project)
  }

  private:

   void roles(project) {
    // No role on archived projects
    return [] unless !project || project&.active?

    // Return all roles if ( user is admin) {
    return all_givable_roles if ( user.admin?) {

    ::Authorization.roles(user, project).eager_load(:role_permissions)
  }

   void cache() {
    this->cache ||= {}
  }

   void all_givable_roles() {
    this->all_givable_roles ||= Role.givable.to_a
  }
}
