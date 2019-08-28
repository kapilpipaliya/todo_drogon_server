#include "user.h"
#include <chrono>
#include "dba.h"
using namespace  madmin;
using namespace std::chrono;
typedef sqlb::SelectedColumn S;
User::User(const MAdminContextPtr &context_): BaseService(context_)
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
        S({"Id", "id", "", "e", PG_TYPES::INT8}),
        S({"Account Type", "type", "", "e", PG_TYPES::ENUM}),
        //S({"no", "no", "", "e", PG_TYPES::TEXT}),
        //S({"sequence_id", "sequence_id", "", "e", PG_TYPES::INT8, false}),
        sqlb::SelectedColumn({"Parent", "parent_id", "", "e", PG_TYPES::INT8, true, 1, 1 }),
        sqlb::SelectedColumn({"username", "username", "", "p", PG_TYPES::TEXT, false, 0, 0, false}),
        S({"User Name", "username", "", "e", PG_TYPES::TEXT}),
        S({"Full Name", "fullname", "", "e", PG_TYPES::TEXT}),
        S({"Create Date", "create_date", "", "e", PG_TYPES::TIMESTAMP}),
        S({"Active", "disabled", "", "e", PG_TYPES::BOOL}),
        S({"Email", "email", "", "e", PG_TYPES::TEXT, true}),
        S({"Password", "password", "", "e", PG_TYPES::TEXT, true}),
        S({"City", "city", "", "e", PG_TYPES::TEXT, true}),
        S({"State", "state", "", "e", PG_TYPES::TEXT, true}),
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
    } else if (event_cmp == "header") { // required
        return headerData(event, args);
    } else if (event_cmp == "data") { // required
        if(context->user.type == "super admin"){
            return allData(event, args);
        } else if (context->user.type == "admin"){
            t.m_query.cusm_where() = format("e.parent_id = {}", context->user_id);
            return allData(event, args);
        } else {
            return {{event, "unauthorised"}};
        }
    } else if (event_cmp == "update_password") {
        if(get_password() == args["old_password"].get<std::string>()){
            if(update_password(args["new_password"].get<std::string>())){
                return {simpleJsonSaveResult(event, true, "Done")};
            }
        }
        return {simpleJsonSaveResult(event, false, "UnAuthorised")};
    } else if (event_cmp  == "ins") {
        return ins(event, args);
    } else if (event_cmp  == "upd") {
        return upd(event, args);
    } else if (event_cmp  == "del") {
        return del(event, args);
    } else if (event_cmp  == "count") {
        return count(event, args);
    } else {
        return nullptr;
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

User User::get_from_username(std::string username)
{

}

User User::get_from_apikey(std::string apikey)
{

}

std::vector<User::Catalog> User::get_catalogs()
{

}

bool User::is_logged_in()
{
    //auto sql = "SELECT id,ip FROM session WHERE username=1 AND expire > now()";
    if (context->current_session_id != 0) { return true; } else { return false; }
}

std::string User::get_password()
{
    auto sql        = "SELECT * FROM music.user WHERE id = $1";
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto transPtr = clientPtr->newTransaction();
        auto r = transPtr->execSqlSync(sql, this->context->user_id);
        if (r.size() == 1) {
            return r[0]["password"].as<std::string>();
        }
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
    }
    return "";
}

long User::create(std::string username, std::string fullname, std::string email, std::string website, std::string password, std::string access, std::string state, std::string city, bool disabled)
{
    //website     = rtrim($website, "/");
    //string password    = hash('sha256', $password);
    //bool disabled    = $disabled ? 1 : 0;

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

    sql += ") VALUES($, $, $, $, $, $, $";

    if (!website.empty()) {
        sql += ", $";
    }
    if (!state.empty()) {
        sql += ", $";
    }
    if (!city.empty()) {
        sql += ", $";
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
        auto r = transPtr->execSqlSync(sql, this->context->user_id, new_password);
        if (r.affectedRows() == 1) {
            return true;
        }
        // todo: save updated password in cache...
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
    }
    return false;
}
