#pragma once
namespace openproj {
namespace Authorization {
class UserAllowedService {
  // attr_accessor :user

//   UserAllowedService(user, role_cache: User::ProjectRoleCache.new(user)) {
//    this->user = user
//    this->project_role_cache = role_cache
//  }

  // Return true if the user is allowed to do the specified action on a specific context
  // Action can be:
  // * a parameter-like Hash (eg. controller: '/projects', action: 'edit')
  // * a permission Symbol (eg. :edit_project)
  // Context can be:
  // * a project : returns true if user is allowed to do the specified action on this project
  // * a group of projects : returns true if user is allowed on every project
  // * nil with options[:global] set : check if user has at least one role allowed for this action,
  //   or falls back to Non Member / Anonymous permissions depending if the user is logged
//   void call(action, context, options = {}) {
//    if ( supported_context?(context, options)) {
//      ServiceResult.new(success: true,
//                        result: allowed_to?(action, context, options))
//    else
//      ServiceResult.new(success: false,
//                        result: false)
//    }
//  }

//   void preload_projects_allowed_to(action) {
//    project_authorization_cache.cache(action)
//  }

  private:

  // attr_accessor :project_role_cache

//   void allowed_to?(action, context, options = {}) {
//    action = normalize_action(action)

//    if ( context.nil? && options[:global]) {
//      allowed_to_globally?(action, options)
//    } else if ( context.is_a? Project) {
//      allowed_to_in_project?(action, context, options)
//    } else if ( context.respond_to?(:to_a)) {
//      context = context.to_a
//      // Authorize if ( user is authorized on every element of the array) {
//      context.present? && context.all? { |project|
//        allowed_to?(action, project, options)
//      }
//    else
//      false
//    }
//  }

//   void allowed_to_in_project?(action, project, _options = {}) {
//    if ( project_authorization_cache.cached?(action)) {
//      return project_authorization_cache.allowed?(action, project)
//    }

//    // No action allowed on archived projects
//    return false unless project.active?
//    // No action allowed on disabled modules
//    return false unless project.allows_to?(action)
//    // Admin users are authorized for anything else
//    if ( user.admin?) { return true ;}

//    has_authorized_role?(action, project)
//  }

  // Is the user allowed to do the specified action on any project?
  // See allowed_to? for the actions and valid options.
//   void allowed_to_globally?(action, _options = {}) {
//    // Admin users are always authorized
//    if ( user.admin?) { return true ;}

//    has_authorized_role?(action)
//  }

//   void has_authorized_role?(action, project = nil) {
//    project_role_cache
//      .fetch(project)
//      .any? { |role|
//      role.allowed_to?(action)
//    }
//  }

//   void project_authorization_cache() {
//    this->project_authorization_cache ||= User::ProjectAuthorizationCache.new(user)
//  }

//   void normalize_action(action) {
//    if ( action.is_a?(Hash) && action[:controller] && action[:controller].to_s.starts_with?('/')) {
//      action = action.dup
//      action[:controller] = action[:controller][1..-1]
//    }

//    action
//  }

//   void supported_context?(context, options) {
//    (context.nil? && options[:global]) ||
//      context.is_a?(Project) ||
//      (!context.nil? && context.respond_to?(:to_a))
//  }
};
}
}
