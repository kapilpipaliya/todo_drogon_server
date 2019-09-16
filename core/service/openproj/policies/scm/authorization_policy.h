#pragma once
namespace openproj {
namespace policy {
namespace Scm {

class AuthoriziationPolicy{
//  attr_reader :project, :user

//   AuthoriziationPolicy(project, user) {
//    this->user = user
//    this->project = project
//  }

  //
  // Determines the authorization status for the user of this project
  // for a given repository request.
  // May be overridden by descendents when more than the read/write distinction
  // is necessary.
//   void authorized?(params) {
//    (readonly_request?(params) && read_access?) || write_access?
//  }

  protected:

  //
  // Determines whether the given request is a read access
  // Must be implemented by descendents of this policy.
//   void readonly_request?(_params) {
//    raise NotImplementedError
//  }

  //
  // Returns whether the user has read access permission to the repository
//   void read_access?() {
//    user.allowed_to?(:browse_repository, project)
//  }

  //
  // Returns whether the user has read/write access permission to the repository
//   void write_access?() {
//    user.allowed_to?(:commit_access, project)
//  }
};
}
}
}
