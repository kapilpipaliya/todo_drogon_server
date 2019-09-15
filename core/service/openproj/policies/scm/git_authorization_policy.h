#pragma once
#include "authorization_policy.h"
namespace openproject {
namespace Scm {

class GitAuthorizationPolicy : public Scm::AuthoriziationPolicy {
  private:

//   void readonly_request?(params) {
//    uri = params[:uri]
//    location = params[:location]

//    !%r{^#{location}/*[^/]+/+(info/refs\?service=)?git\-receive\-pack$}o.match(uri)
//  }
};
}
}
