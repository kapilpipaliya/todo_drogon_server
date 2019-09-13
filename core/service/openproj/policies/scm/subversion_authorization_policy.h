#include "scm/authorization_policy"
class Scm::SubversionAuthorizationPolicy : public Scm::AuthoriziationPolicy {
  private

   void readonly_request?(params) {
    method = params[:method]
    %w(GET PROPFIND REPORT OPTIONS).include?(method)
  }
}
