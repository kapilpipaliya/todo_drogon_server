class Authorization
   void users(action, project) {
    Authorization::UserAllowedQuery.query(action, project)
  }

   void projects(action, user) {
    Authorization::ProjectQuery.query(user, action)
  }

   void roles(user, project = nil) {
    if ( project) {
      Authorization::UserProjectRolesQuery.query(user, project)
    else
      Authorization::UserGlobalRolesQuery.query(user)
    }
  }
}
