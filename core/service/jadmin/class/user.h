#ifndef USER_H
#define USER_H

#include <fmt/format.h>
#include <string>
#include <vector>
#include "json.hpp"
#include "spdlogfix.h"

using std::string;
/**
 * User Class
 *
 * This class handles all of the user related functions includingn the creationg
 * and deletion of the user objects from the database by defualt you constrcut
 * it with a user_id from user.id
 *
 */
#include "../../../../wscontroller/context/jadmincontext.h"
#include "../../baseserviceabs.h"

using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
/**
 * User Class
 *
 * This class handles all of the user related functions includingn the creationg
 * and deletion of the user objects from the database by defualt you constrcut
 *it with a user_id from user.id
 **/
class User : public BaseServiceAbs {
  struct Info {
    string username;
    string fullname;
    int access{};
  };

  struct Count {
    int users{0};
    int connected{0};
  };
  struct Catalog {};

 public:
  User(JAdminContextPtr);
  // User(int user_id);
  void setupTable() override;
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args) override;
  nlohmann::json getUserTypeFormData();

  // static Count count();
  static void get_valid_users();  // fix it..
  // static User get_from_username(string username); // fix
  // static User get_from_apikey(string apikey); //fix
  // public static User get_from_email(email); //fix
  // static User get_from_website(website); //fix

  // Basic Componets
  //        int id;
  //        string username;
  //       string fullname;
  //        bool fullname_public;
  //        int access;
  //       bool disabled;
  //        string email;
  //        int last_seen;
  //        int create_date;
  //        string validation;
  //        string website;
  //        string state;
  //        string city;
  //        string apikey;

  // Constructed variables
  /**
   * @var array prefs
   */
  // public prefs = array();
  /**
   * @var Tmp_Playlist playlist
   */
  //        public playlist;
  //        string f_name;
  //        string f_last_seen;
  //        string f_create_date;
  //        string link;
  //        string f_link;
  //        string f_useage;
  //        string ip_history;
  //        string f_avatar;
  //        string f_avatar_mini;
  //        string f_avatar_medium;

  /**
   * count
   *
   * This returns the number of user accounts that exist.
   */
  // static void  count();
  /**
   * _get_info
   * This function returns the information for this object
   */
  // private function _get_info();
  /**
   * load_playlist
   * This is called once per page load it makes sure that this session
   * has a tmp_playlist, creating it if it doesn't, then sets this->playlist
   * as a tmp_playlist object that can be fiddled with later on
   */
  // void load_playlist();
  /**
   * get_valid_users
   * This returns all valid users in database.
   */
  // static void  get_valid_users();
  /**
   * get_from_username
   * This returns a built user from a username. This is a
   * static function so it doesn't require an instance
   */
  // static void  get_from_username(username);
  /**
   * get_from_apikey
   * This returns a built user from an apikey. This is a
   * static function so it doesn't require an instance
   */
  // static void  get_from_apikey(apikey);
  /**
   * get_from_email
   * This returns a built user from a email. This is a
   * static function so it doesn't require an instance
   */
  // static void  get_from_email(email);
  /**
   * get_from_website
   * This returns users list related to a website.
   */
  // static void  get_from_website(website);
  /**
   * get_catalogs
   * This returns the catalogs as an array of ids that this user is allowed to
   * access
   */
  // void get_catalogs();
  /**
   * get_preferences
   * This is a little more complicate now that we've got many types of
   * preferences This funtions pulls all of them an arranges them into a spiffy
   * little array You can specify a type to limit it to a single type of
   * preference
   * []['title'] = ucased type name
   * []['prefs'] = array(array('name','display','value'));
   * []['admin'] = t/f value if this is an admin only section
   */
  // void get_preferences(type = 0, system = false);
  /**
   * set_preferences
   * sets the prefs for this specific user
   */
  // void set_preferences();
  /**
   * get_favorites
   * returns an array of your type favorites
   */
  // void get_favorites(type);
  /**
   * get_recommendations
   * This returns recommended objects of type. The recommendations
   * are based on voodoo economics,the phase of the moon and my current BAL.
   */
  // void get_recommendations(type);
  /**
   * is_logged_in
   * checks to see if this user is logged in returns their current IP if they
   * are logged in
   */
  bool is_logged_in();
  /**
   * has_access
   * this function checkes to see if this user has access
   * to the passed action (pass a level requirement)
   */
  // void has_access(needed_level);
  /**
   * is_registered
   * Check if the user is registered
   * @return boolean
   */
  // static //void  is_registered();
  /**
   * update
   * This function is an all encompasing update function that
   * calls the mini ones does all the error checking and all that
   * good stuff
   */
  // void update(array data);
  /**
   * update_username
   * updates their username
   */
  // void update_username(new_username);
  /**
   * update_validation
   * This is used by the registration mumbojumbo
   * Use this function to update the validation key
   * NOTE: crap this doesn't have update_item the humanity of it all
   */
  // void update_validation(new_validation);
  /**
   * update_fullname
   * updates their fullname
   */
  // void update_fullname(new_fullname);
  /**
   * update_fullname_public
   * updates their fullname public
   */
  // void update_fullname_public(new_fullname_public);
  /**
   * update_email
   * updates their email address
   */
  // void update_email(new_email);
  /**
   * update_website
   * updates their website address
   */
  // void update_website(new_website);
  /**
   * update_state
   * updates their state
   */
  // void update_state(new_state);
  /**
   * update_city
   * updates their city
   */
  // void update_city(new_city);
  /**
   * update_apikey
   * Updates their api key
   */
  // void update_apikey(new_apikey);
  /**
   * generate_apikey
   * Generate a new user API key
   */
  // void generate_apikey();
  /**
   * get_password
   * Get the current hashed user password from database.
   */
  string get_password();
  /**
   * disable
   * This disables the current user
   */
  // void disable();
  /**
   * enable
   * this enables the current user
   */
  // void enable();
  /**
   * update_access
   * updates their access level
   */
  // void update_access(new_access);
  /*!
      @function update_last_seen
      @discussion updates the last seen data for this user
  */
  // void update_last_seen();
  /**
   * update_user_stats
   * updates the playcount mojo for this specific user
   */
  // void update_stats(media_type, media_id, agent = '', location = array(),
  // noscrobble = false);
  /**
   * insert_ip_history
   * This inserts a row into the IP History recording this user at this
   * address at this time in this place, doing this thing.. you get the point
   */
  // void insert_ip_history();
  /**
   * create
   * inserts a new user into ampache
   */
  static long create(const string& username, const string& fullname,
                     const string& email, const string& website,
                     const string& password, const string& access,
                     const string& state = "", const string& city = "",
                     bool disabled = false);
  /**
   * update_password
   * updates a users password
   */
  bool update_password(string new_password);
  /**
   * format
   * This function sets up the extra variables we need when we are displaying a
   * user for an admin, these should not be normally called when creating a
   * user object
   */
  // void format(details = true);
  /**
   * access_name_to_level
   * This takes the access name for the user and returns the level
   */
  // static //void  access_name_to_level(level);
  /**
   * fix_preferences
   * This is the new fix_preferences function, it does the following
   * Remove Duplicates from user, add in missing
   * If -1 is passed it also removes duplicates from the preferences
   * table.
   */
  // static //void  fix_preferences(user_id);
  /**
   * delete
   * deletes this user and everything associated with it. This will affect
   * ratings and tottal stats
   */
  bool delNew(long user_id);
  /**
   * is_online
   * delay how long since last_seen in seconds default of 20 min
   * calcs difference between now and last_seen
   * if less than delay, we consider them still online
   */
  // void is_online(delay = 1200);
  /**
   * get_user_validation
   *if user exists before activation can be done.
   */
  // static //void  get_validation(username);
  /**
   * get_recently_played
   * This gets the recently played items for this user respecting
   * the limit passed
   */
  // void get_recently_played(limit, type='');
  /**
   * get_ip_history
   * This returns the ip_history from the
   * last AmpConfig::get('user_ip_cardinality') days
   */
  // void get_ip_history(count='', distinct='');
  /**
   * Get item fullname.
   * @return string
   */
  // void get_fullname();
  /**
   * get_avatar
   * Get the user avatar
   */
  // void get_avatar(local = false);
  // void update_avatar(data, mime = '');
  // void upload_avatar();
  // void delete_avatar();
  /**
   * activate_user
   * the user from public_registration
   */
  // void activate_user(username);
  /**
   * get_artists
   * Get artists associated with the user
   */
  // void get_artists();
  /**
   * is_xmlrpc
   * checks to see if this is a valid xmlrpc user
   */
  // void is_xmlrpc();
  /**
   * get_followers
   * Get users following this user
   * @return int[]
   */
  // void get_followers();
  /**
   * get_following
   * Get users followed by this user
   * @return int[]
   */
  // void get_following();
  /**
   * is_followed_by
   * Get if an user is followed by this user
   * @param integer user_id
   * @return boolean
   */
  // void is_followed_by(user_id);
  /**
   * is_following
   * Get if this user is following an user
   * @param integer user_id
   * @return boolean
   */
  // void is_following(user_id);
  /**
   * toggle_follow
   * @param integer user_id
   * @return boolean
   */
  // void toggle_follow(user_id);
  /**
   * get_display_follow
   * Get html code to display the follow/unfollow link
   * @param int|null display_user_id
   * @return string
   */
  // void get_display_follow(user_id = null);
  /**
   * check_username
   * This checks to make sure the username passed doesn't already
   * exist in this instance of ampache
   */
  // static void  check_username(username);
  /**
   * rebuild_all_preferences
   * This rebuilds the user preferences for all installed users, called by the
   * plugin functions
   */
  // static void  rebuild_all_preferences();
  /**
   * stream_control
   * Check all stream control plugins
   * @param array media_ids
   * @param User user
   * @return boolean
   */
  // static void  stream_control(media_ids, User user = null);

 private:
  Info get_info();
  int id{};

  nlohmann::json userRegister(const nlohmann::json& event, nlohmann::json args);
  nlohmann::json userLogin(const nlohmann::json& event, nlohmann::json args);
  nlohmann::json userId(const nlohmann::json& event,
                        const nlohmann::json& args);
  nlohmann::json checkout(const nlohmann::json& event,
                          const nlohmann::json& args);

  JAdminContextPtr context;
};
}  // namespace jadmin
#endif  // USER_H
