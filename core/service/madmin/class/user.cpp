#include "user.h"
#include <chrono>
#include "dba.h"
using namespace  madmin;
using namespace std::chrono;
User::User(int user_id)
{
    if(!user_id){
        // return false;
    }
    auto info = get_info();

}
/**
 * _get_info
 * This function returns the information for this object
 */
Info User::get_info()
{
    // If user is in cache return from it.
    // If user is system user return system data.

    std::string strSql = fmt::format("SELECT username, fullname, access FROM {} WHERE id=$1", id);
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto res = clientPtr->execSqlSync( strSql, id);
        Info info;
        info.username = res[0]["username"].as<std::string>();
        info.fullname = res[0]["fullname"].as<std::string>();
        info.access = res[0]["access"].as<int>();
        return info;
    } catch (const std::exception &e) {
        spdlog::error(e.what());
        Info info;
        return info;
    }
    // add user to the cache
}
/**
 * count
 *
 * This returns the number of user accounts that exist.
 */
Count User::count()
{
    Count count;
    //1
    std::string strSql = fmt::format("SELECT COUNT(id) FROM music.user");
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto res = clientPtr->execSqlSync(strSql);
        count.users = res[0]["count"].as<int>();
    } catch (const std::exception &e) {
        spdlog::error(e.what());
    }
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto res = clientPtr->execSqlSync(strSql);
        count.users = res[0]["count"].as<int>();
    } catch (const std::exception &e) {
        spdlog::error(e.what());
    }


    //2
    // https://stackoverflow.com/questions/14504870/convert-stdchronotime-point-to-unix-timestamp
    //auto unix_timestamp = std::chrono::seconds(std::time(nullptr));
    //int last_seen = unix_timestamp - 1200;
    //std::string lastSql = fmt::format("SELECT COUNT(DISTINCT session.username) FROM session INNER JOIN user ON session.username = user.username "
    //                                  "WHERE session.expire > $1 and user.last_seen > $2");
    return count;
}
/**
 * load_playlist
 * This is called once per page load it makes sure that this session
 * has a tmp_playlist, creating it if it doesn't, then sets $this->playlist
 * as a tmp_playlist object that can be fiddled with later on
 */
void User::load_playlist()
{
    //playlist_id = Tmp_Playlist::get_from_session($session_id);
}

void User::get_valid_users()
{
    std::string sql = fmt::format("SELECT id FROM user WHERE disabled = false");
    auto db_results = Dba::read(sql);
    for (auto r : db_results) {

    }
}

User User::get_from_username(std::string username)
{

}

User User::get_from_apikey(std::string apikey)
{

}

std::vector<Catalog> User::get_catalogs()
{

}
