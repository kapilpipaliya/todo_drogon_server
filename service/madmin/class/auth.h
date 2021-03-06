#ifndef AUTH_H
#define AUTH_H

#include "../../../../wscontroller/context/madmincontext.h"

#include "sql/query.h"

namespace music {
namespace service {
class Auth {
 public:
  Auth(std::shared_ptr<websocket::music::MAdminContext>);
  void setupTable();
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  /**
   * logout
   *
   * This is called when you want to log out and nuke your session.
   * This is the function used for the Ajax logouts, if no id is passed
   * it tries to find one from the session,
   * @param string key
   * @param boolean relogin
   */
  bool logout(long key = 0, bool relogin = true);  // key = ""
  /**
   * login
   *
   * This takes a username and password and then returns the results
   * based on what happens when we try to do the auth.
   * @param string username
   * @param string password
   * @param boolean allow_ui
   * @return array
   */
  static std::tuple<long, long> login(const std::string& username,
                                      const std::string& password,
                                      bool allow_ui = false);
  /**
   * login_step2
   *
   * This process authenticate step2 for an auth module
   * @param string auth_mod
   * @return array
   */
  // static void  login_step2(auth_mod)
  /**
   * mysql_auth
   *
   * This is the core function of our built-in authentication.
   * @param string username
   * @param string password
   * @return array
   */
 private:
  // void mysql_auth(username, password);
  /**
   * pam_auth
   *
   * Check to make sure the pam_auth function is implemented (module is
   * installed), then check the credentials.
   * @param string username
   * @param string password
   * @return array
   */
  // void pam_auth(username, password);
  /**
   * external_auth
   *
   * Calls an external program compatible with mod_authnz_external
   * such as pwauth.
   * @param string username
   * @param string password
   * @return array
   */
  // void external_auth(username, password);
  /**
   * ldap_auth
   * @param string username
   * @param string password
   * @return array
   */
  // void ldap_auth(username, password);
  /**
   * http_auth
   * This auth method relies on HTTP auth from the webserver
   *
   * @param string username
   * @param string password
   * @return array
   * @SuppressWarnings(PHPMD.UnusedFormalParameter)
   */
  // void http_auth(username, password);
  /**
   * openid_auth
   * Authenticate user with OpenID
   *
   * @param string username
   * @param string password
   * @return array
   * @SuppressWarnings(PHPMD.UnusedFormalParameter)
   */
  // void openid_auth(username, password);
  /**
   * openid_auth_2
   * Authenticate user with OpenID, step 2
   * @return array
   */
  // void openid_auth_2();
  nlohmann::json saveFileMeta(const nlohmann::json& event, nlohmann::json args);

 private:
  std::shared_ptr<websocket::music::MAdminContext> context;
  sql::Query query;
};
}  // namespace service
}  // namespace music
#endif  // AUTH_H
