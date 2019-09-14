#include "scm/authorization_policy"
namespace openproject {
class Scm::GitAuthorizationPolicy : public Scm::AuthoriziationPolicy {
  private:

   void readonly_request?(params) {
    uri = params[:uri]
    location = params[:location]

    !%r{^#{location}/*[^/]+/+(info/refs\?service=)?git\-receive\-pack$}o.match(uri)
  }
}
