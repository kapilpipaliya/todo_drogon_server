#pragma once

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
/**
 *
 * This class handles all of the session related stuff in Ampache
 *
 */
namespace madmin {
class Session : public BaseServiceAbs {
 public:
  Session(MAdminContextPtr);
  void setupTable() override;

  /**
   * open
   *
   * This is run on the beginning of a session, nothing to do here for now.
   */
  // static void open();
  /**
   * close
   *
   * This is run on the end of a session, nothing to do here for now.
   */
  // static void close();
  /**
   * write
   *
   * This saves the session information into the database.
   */
  // static void write(std::string key, std::string value);
  /**
   * destroy
   *
   * This removes the specified session from the database.
   */
  static bool destroy(long key);
  /**
   * gc
   *
   * This function is randomly called and it cleans up the spoo
   */
  // static void gc();
  /**
   * read
   *
   * This takes a key and returns the data from the database.
   */
  // static void read(std::string key);
  /**
   * _read
   *
   * This returns the specified column from the session row.
   */
  // private static function _read(std::string key, std::string column);
  /**
   * username
   *
   * This returns the username associated with a session ID, if any
   */
  // static void username(std::string key);
  /**
   * username
   *
   * This returns the agent associated with a session ID, if any
   */
  // static void agent(std::string key);
  /**
   * create
   * This is called when you want to create a new session
   * it takes care of setting the initial cookie, and inserting the first
   * chunk of data, nifty ain't it!
   */
  // static void create(std::string data);
  /**
   * check
   *
   * This checks for an existing session. If it's still valid we go ahead
   * and start it and return true.
   */
  // static void check();
  /**
   * exists
   *
   * This checks to see if the specified session of the specified type
   * exists
   * based on the type.
   */
  // static void exists(std::string type, std::string key);
  /**
   * extend
   *
   * This takes a SID and extends its expiration.
   */
  // static void extend(std::string sid, std::string type = null);
  /**
   * update_username
   *
   * This takes a SID and update associated username.
   */
  // static void update_username(std::string sid, std::string username);
  /**
   * update_geolocation
   * Update session geolocation.
   * @param string std::string sid
   * @param float std::string latitude
   * @param float std::string longitude
   */
  // static void update_geolocation(std::string sid, std::string latitude,
  // std::string longitude, std::string name);
  /**
   * get_geolocation
   * Get session geolocation.
   * @param string std::string sid
   * @return array
   */
  // static void get_geolocation(std::string sid);
  /**
   * _auto_init
   *
   * This function is called when the object is included, this sets up the
   * session_save_handler
   */
  // static void _auto_init();
  /**
   * create_cookie
   *
   * This is separated into its own function because of some flaws in
   * specific webservers *cough* IIS *cough* which prevent us from setting
   * a cookie at the same time as a header redirect. As such on view of a
   * login a cookie is set with the proper name.
   */
  // static void create_cookie();
  /**
   * create_user_cookie
   *
   * This function just creates the user cookie wich contains current username.
   * It must be used for information only.
   *
   * It also creates a cookie to store used language.
   */
  /**
   * create_remember_cookie
   *
   * This function just creates the remember me cookie, nothing special.
   */
  // static void create_remember_cookie(std::string username);
  /**
   * Generate a random token.
   * @return string
   */
  // static void generateRandomToken();
  // static void storeTokenForUser(std::string username, std::string token,
  // std::string remember_length); static void auth_remember();
  /**
   * ungimp_ie
   *
   * This function sets the cache limiting to public if you are running
   * some flavor of IE and not using HTTPS.
   */
  // static void ungimp_ie();
 private:
  MAdminContextPtr context;
};
}  // namespace madmin
