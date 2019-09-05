#include "user.h"
#include <chrono>
#include <utility>
#include <utility>
#include "../../dba.h"
using namespace  madmin;
using namespace std::chrono;
using S = sqlb::SelectedColumn;
User::User(MAdminContextPtr context_): context(std::move(context_))
{
    t.m_table = sqlb::ObjectIdentifier("music", "user", "e");
    t.m_query = sqlb::Query(t.m_table);
}
//User::User(int user_id)
//{
//    if(!user_id){
//        // return false;
//    }
//    auto info = get_info();

//}

void User::setupTable()
{

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        S({"ID No", "id", "", "e", PG_TYPES::INT8}),
        S({"Account Type", "type", "", "e", PG_TYPES::ENUM}),
        //S({"no", "no", "", "e", PG_TYPES::TEXT}),
        //S({"sequence_id", "sequence_id", "", "e", PG_TYPES::INT8, false}),
        S({"User Name", "username", "", "e", PG_TYPES::TEXT}),
        S({"Password", "password", "", "e", PG_TYPES::TEXT, true}),
        S({"Full Name", "fullname", "", "e", PG_TYPES::TEXT}),
        S({"Parent User Name", "parent_id", "", "e", PG_TYPES::INT8, true, 1, 1 }),
        S({"username", "username", "", "p", PG_TYPES::TEXT, false, 0, 0, false}),
        S({"Create Date", "create_date", "", "e", PG_TYPES::TIMESTAMP}),
        S({"Disabled", "disabled", "", "e", PG_TYPES::BOOL}),
//        S({"Email", "email", "", "e", PG_TYPES::TEXT, true}),
//        S({"City", "city", "", "e", PG_TYPES::TEXT, true}),
//        S({"State", "state", "", "e", PG_TYPES::TEXT, true}),
        //S({"Created By", "create_user_id", "", "e", PG_TYPES::INT8, true, 1, 0, false}), S({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
        //S({"Updated By", "update_user_id", "", "e", PG_TYPES::INT8, true, 1, 0, false}), S({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
        //S({"Create Time", "inserted_at", "", "e", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
        //S({"Update Time", "updated_at", "", "e", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
    };
    auto p = sqlb::ObjectIdentifier("music", "user", "p");
    //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
                sqlb::Join("left", p, "e.parent_id = p.id")
            //sqlb::Join("left", u1, "e.create_user_id = u1.id"),
            //sqlb::Join("left", u2, "e.update_user_id = u2.id"),
            };

    t.m_query.groupBy() = {
        };
}

nlohmann::json User::handleEvent(nlohmann::json event, unsigned long next, nlohmann::json args)
{
    auto event_cmp = event[next].get<std::string>();
    if(event_cmp == "is_logged_in"){
        json res = {{event}};
        res[0][1] = is_logged_in();
        return res;
    } if (event_cmp == "header") { // required
        return headerData(event, args);
    } else if (event_cmp == "data") { // required
        if(context->user.type == "super admin"){
            return allData(event, args);
        } if (context->user.type == "admin"){
            t.m_query.cusm_where() = format("e.parent_id = {}", context->user_id);
            return allData(event, args);
        } else {
            return {{event, "unauthorised"}};
        }
    } else if (event_cmp == "update_password") {
        if(!args.is_array()) return {simpleJsonSaveResult(event, false, "Not Valid Args")};
        if(get_password() == args[0]["old_password"].get<std::string>()){
            if(update_password(args[0]["new_password"].get<std::string>())){
                return {simpleJsonSaveResult(event, true, "Done")};
            }
        }
        return {simpleJsonSaveResult(event, false, "UnAuthorised")};
    } else if (event_cmp  == "user_types_form_data") {
         return {{event, getUserTypeFormData()}};
    } else if (event_cmp  == "ins") {
        args[0]["parent_id"] = context->user_id;
        return ins(event, args);
    } else if (event_cmp  == "upd") {
        return upd(event, args);
    } else if (event_cmp  == "del") {
        if(args[0].is_array()){
            if(args[0][0].is_number()){
                if(delNew(args[0][0].get<long>())){
                    return {simpleJsonSaveResult(event, true, "Done")};
                }
            }
        }
        //return del(event,args);
        return {simpleJsonSaveResult(event, false, "UnAuthorised")};
    } else if (event_cmp  == "count") {
        return count(event, args);
    } else {
        return nullptr;
    }
}

nlohmann::json User::getUserTypeFormData()
{
    if(context->user.type == "super admin"){
        json j = json::array({
                                    json::array({"Super Admin","super admin"}),
                                    json::array({"Admin","admin"}),
                                    json::array({"Executive","executive"}),
        });
        return j;
    } if (context->user.type == "admin"){
        json j = json::array({
                                 json::array({"Executive","executive"}),
        }) ;
        return j;
    } else {
        return json::array();
    }
}

User::Info User::get_info()
{
    // If user is in cache return from it.
    // If user is system user return system data.

    std::string strSql = fmt::format("SELECT username, fullname, access FROM {} WHERE id=1", id);
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto res = clientPtr->execSqlSync( strSql, id);
        Info info;
        info.username = res[0]["username"].as<std::string>();
        info.fullname = res[0]["fullname"].as<std::string>();
        info.access = res[0]["access"].as<int>();
        return info;
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
        Info info;
        return info;
    }
    // add user to the cache
}

/*User::Count User::count()
{
    Count count;
    //1
    std::string strSql = fmt::format("SELECT COUNT(id) FROM music.user");
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto res = clientPtr->execSqlSync(strSql);
        count.users = res[0]["count"].as<int>();
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
    }
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto res = clientPtr->execSqlSync(strSql);
        count.users = res[0]["count"].as<int>();
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
    }


    //2
    // https://stackoverflow.com/questions/14504870/convert-stdchronotime-point-to-unix-timestamp
    //auto unix_timestamp = std::chrono::seconds(std::time(nullptr));
    //int last_seen = unix_timestamp - 1200;
    //std::string lastSql = fmt::format("SELECT COUNT(DISTINCT session.username) FROM session INNER JOIN user ON session.username = user.username "
    //                                  "WHERE session.expire > 1 and user.last_seen > 2");
    return count;
}
*/
void User::load_playlist()
{
    //playlist_id = Tmp_Playlist::get_from_session(session_id);
}

void User::get_valid_users()
{
    std::string sql = fmt::format("SELECT id FROM user WHERE disabled = false");
    auto db_results = Dba::read(sql);
    for (auto r : db_results) {

    }
}

//User User::get_from_username(std::string username)
//{

//}

//User User::get_from_apikey(std::string apikey)
//{

//}

//std::vector<User::Catalog> User::get_catalogs()
//{

//}

bool User::is_logged_in()
{
    //auto sql = "SELECT id,ip FROM session WHERE username=1 AND expire > now()";
    return context->current_session_id != 0;:string User::get_password()
{
    auto sql        = "SELECT * FROM music.user WHERE id = $1";
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto transPtr = clientPtr->newTransaction();
        auto r = Dba::writeInTrans(transPtr, sql, this->context->user_id);
        if (r.size() == 1) {
            return r[0]["password"].as<std::string>();
        }
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
    }
    return "";
}

long User::create(const std::string&  /*username*/, const std::string&  /*fullname*/, const std::string&  /*email*/, const std::string&  /*website*/, const std::string&  /*password*/, const std::string&  /*access*/, const std::string&  /*state*/, const std::string&  /*city*/, bool  /*disabled*/)
{
    //website     = rtrim(website, "/");
    //string password    = hash('sha256', password);
    //bool disabled    = disabled $ 1 : 0;

    /* Now Insert this new user */
    /* Great Logic..
    string sql = "INSERT INTO music.user (username, disabled, fullname, email, password, access, create_date";
    string params = array(username, disabled, fullname, email, password, access, time());

    if (!website.empty()) {
        sql += ", website";
        params[] = website;
    }
    if (!state.empty()) {
        sql += ", state";
        params[] = state;
    }
    if (!city.empty()) {
        sql += ", city";
        params[] = city;
    }

    sql += ") VALUES(, , , , , , ";

    if (!website.empty()) {
        sql += ", ";
    }
    if (!state.empty()) {
        sql += ", ";
    }
    if (!city.empty()) {
        sql += ", ";
    }

    sql += ")";
    db_results = Dba::write(sql, params);

    if (!db_results) {
        return false;
    }

    // Get the insert_id
    string insert_id = Dba::insert_id();
    */

    /* Populates any missing preferences, in this case all of them */
    //self::fix_preferences(insert_id);

    //return insert_id;
    return 0;
}

bool User::update_password(std::string new_password)
{
    // std::string new_password = hash('sha256', new_password);
    //new_password = Dba::escape(new_password);
    std::string sql          = "UPDATE music.user SET password = $2 WHERE id = $1";
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto transPtr = clientPtr->newTransaction();
        auto r = Dba::writeInTrans(transPtr, sql, this->context->user_id, std::move(new_password));
        if (r.affectedRows() == 1) {
            return true;
        }
        // todo: save updated password in cache...
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
    }
    return false;
}

bool User::delNew(long user_id)
{
    /*
      Before we do anything make sure that they aren't the last
      admin
    */
    //if (this->has_access(100)) {
        //sql        = "SELECT id FROM user WHERE access='100' AND id != $";
        //db_results = Dba::read(sql, user_id);
        //if (!Dba::num_rows(db_results)) {
        //    return false;
        //}
    auto sql        = "SELECT id FROM music.user WHERE access='100' AND  id <> $1";
    auto db_results = Dba::read(sql, user_id);
    if (!Dba::num_rows(db_results)) {
                return false;
    }
    //} // if this is an admin check for others

    // Delete their playlists
    auto sql1 = "DELETE FROM music.playlist WHERE user_id = $1";
    Dba::write(sql1, user_id);

    // Clean up the playlist data table
    //auto sql2 = "DELETE FROM music.playlist_data USING playlist_data "
     //   "LEFT JOIN playlist ON playlist.id=playlist_data.playlist "
       // "WHERE playlist.id IS NULL";
   // Dba::write(sql2);

    // Delete any stats they have
    auto sql3 = "DELETE FROM music.object_count WHERE user_id = $1";
    Dba::write(sql3, user_id);

    // Clear the IP history for this user
    auto sql4 = "DELETE FROM music.ip_history WHERE user_id = $1";
    Dba::write(sql4, user_id);

    // Nuke any access lists that are specific to this user
    auto sql5 = "DELETE FROM music.access_list WHERE user_id = $1";
    Dba::write(sql5, user_id);

    // Delete their ratings
    auto sql6 = "DELETE FROM music.rating WHERE user_id = $1";
    Dba::write(sql6, user_id);

    // Delete their tags
    auto sql7 = "DELETE FROM music.tag_map WHERE user_id = $1";
    Dba::write(sql7, user_id);

    // Clean out the tags
    //auto sql8 = "DELETE FROM music.tag USING tag_map LEFT JOIN music.tag_map ON tag_map.id=tag.map_id AND tag_map.id IS NULL";
    //Dba::write(sql8);

    // Delete their preferences
    auto sql9 = "DELETE FROM music.user_preference WHERE user_id = $1";
    Dba::write(sql9, user_id);

    // Delete their voted stuff in democratic play
    auto sql10 = "DELETE FROM music.user_vote WHERE user_id = $1";
    Dba::write(sql10, user_id);

    // Delete their shoutbox posts
    auto sql11 = "DELETE FROM music.user_shout WHERE user_id = $1";
    Dba::write(sql11, user_id);

    // Delete their private messages posts
    auto sql12 = "DELETE FROM music.user_pvmsg WHERE from_user_id = $1 OR to_user_id = $2";
    Dba::write(sql12, user_id, user_id);

    // Delete their following/followers
    auto sql13 = "DELETE FROM music.user_follower WHERE user_id = $1 OR follow_user_id = $2";
    Dba::write(sql13, user_id, user_id);

    // Added
    auto sql15 = "DELETE FROM music.user_activity WHERE user_id = $1";
    Dba::write(sql15, user_id);
    // Added
    auto sql16 = "DELETE FROM music.search WHERE user_id = $1";
    Dba::write(sql16, user_id);
    auto sql17 = "DELETE FROM music.session WHERE user_id = $1";
    Dba::write(sql17, user_id);

    // Delete the user itself
    auto sql14 = "DELETE FROM music.user WHERE id = $1";
    Dba::write(sql14, user_id);



//    auto sql15 = "DELETE FROM music.session WHERE username = $";
//    Dba::write(sql, array(this->username));

    return true;
}
