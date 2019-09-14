// project, projects, global, user = nil

class AuthorizationService
  // @params
  //   ctrl - controller
  //   action - action
  // this->named params
  //   context - single project or array of projects - default nil
  //   global - global - default false
  //   user - user - default current user
   AuthorizationService(permission, context: nil, global: false, user: User.current) {
    this->permission = permission
    this->context = context
    this->global = global
    this->user = user
  }

   void call() {
    this->user.allowed_to?(this->permission, this->context, global: this->global)
  }
}
