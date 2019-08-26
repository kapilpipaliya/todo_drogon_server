#ifndef USER_H
#define USER_H

#include <string>
#include <drogon/HttpAppFramework.h>
#include "spdlog/spdlog.h"
#include <fmt/format.h>
#include  "json.hpp"
#include <vector>

using nlohmann:: json;
using namespace fmt::v5;
/**
 * User Class
 *
 * This class handles all of the user related functions includingn the creationg
 * and deletion of the user objects from the database by defualt you constrcut it
 * with a user_id from user.id
 *
 */
namespace madmin {
struct Info{
    std::string username;
    std::string fullname;
    int access;
};

struct Count{
    int users{0};
    int connected{0};
};
struct Catalog{

};

class User
{



public:
    User(int user_id);
    static Count count();
    void load_playlist();
    static void get_valid_users(); // fix it..
    static User get_from_username(std::string username); // fix
    static User get_from_apikey(std::string apikey); //fix
    //public static User get_from_email($email); //fix
    //static User get_from_website($website); //fix

    std::vector<Catalog > get_catalogs();
//    get_preferences($type = 0, $system = false)
//    function set_preferences()
//    function get_favorites($type)
//     function get_recommendations($type)
//    function is_logged_in()
//    function has_access($needed_level)
//    function is_registered()
//    function update(array $data)
//    function update_username($new_username)
//    function update_validation($new_validation)
//    function update_fullname($new_fullname)
//    function update_fullname_public($new_fullname_public)
//    function update_email($new_email)
//    function update_website($new_website)
//    void function update_state($new_state)
//    void function update_city($new_city)
//    void function update_apikey($new_apikey)
//    void function generate_apikey()
//    void function get_password()
//    void function disable()
//    void function enable()
//    void function update_access($new_access)
//    void function update_last_seen()
//    void function update_stats($media_type, $media_id, $agent = '', $location = array(), $noscrobble = false)
//    void function insert_ip_history()
//    void static function create($username, $fullname, $email, $website, $password, $access, $state = '', $city = '', $disabled = false)
//    void function update_password($new_password)
//    void static function access_name_to_level($level)
//    void static function fix_preferences($user_id)
//    void function delete()
//    void function is_online($delay = 1200)
//    void static function get_validation($username)
//    void function get_recently_played($limit, $type='')
//    void function get_ip_history($count='', $distinct='')
//    void function get_fullname()
//    void function get_avatar($local = false)
//    void function update_avatar($data, $mime = '')
//    void function upload_avatar()
//    void function delete_avatar()
//    void function activate_user($username)
//    void function get_artists()
//    void function is_xmlrpc()
//    void function get_followers()
//    void function get_following()
//    void function is_followed_by($user_id)
//    void function is_following($user_id)
//    void function toggle_follow($user_id)
//    void function get_display_follow($user_id = null)
//    void static function check_username($username)
//    void static function rebuild_all_preferences()
//    void static function stream_control($media_ids, User $user = null)

private:
    Info get_info();
    int id;
    int playlist_id;
};
}
#endif // USER_H
