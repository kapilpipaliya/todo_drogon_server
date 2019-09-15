#include "user.h"
#include <chrono>
#include <utility>
#include "../../../sql/dba.h"

// using namespace std::chrono;
namespace jadmin {
User::User(std::shared_ptr<websocket::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("music", "user", "e"));
  setupTable();
}
// User::User(long user_id)
//{
//    if(!user_id){
//        // return false;
//    }
//    auto info = get_info();

//}

void User::setupTable() {}

nlohmann::json User::handleEvent(nlohmann::json event, unsigned long next,
                                 nlohmann::json args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "is_logged_in") {
    nlohmann::json res = {{event}};
    res[0][1] = is_logged_in();
    return res;
  }
  if (event_cmp == "update_password") {
    if (!args.is_array())
      return {
          websocket::WsFns::successJsonObject(event, false, "Not Valid Args")};
    if (get_password() == args[0]["old_password"].get<std::string>()) {
      if (update_password(args[0]["new_password"].get<std::string>())) {
        return {websocket::WsFns::successJsonObject(event, true, "Done")};
      }
    }
    return {websocket::WsFns::successJsonObject(event, false, "UnAuthorised")};
  }
  if (event_cmp == "user_types_form_data") {
    return {{event, getUserTypeFormData()}};
  } else if (event_cmp == "user_register") {
    return userRegister(event, args);
  } else if (event_cmp == "user_id") {
    return userId(event, args);
  } else if (event_cmp == "checkout") {
    return checkout(event, args);
  } else {
    return nullptr;
  }
}

nlohmann::json User::getUserTypeFormData() { return nlohmann::json::array(); }

User::Info User::get_info() {
  // If user is in cache return from it.
  // If user is system user return system data.

  std::string strSql =
      fmt::format("SELECT username, fullname, access FROM {} WHERE id=1", id);
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    auto res = clientPtr->execSqlSync(strSql, id);
    Info info;
    info.username = res[0]["username"].as<std::string>();
    info.fullname = res[0]["fullname"].as<std::string>();
    info.access = res[0]["access"].as<int>();
    return info;
  } catch (const std::exception& e) {
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
    //
https://stackoverflow.com/questions/14504870/convert-stdchronotime-point-to-unix-timestamp
    //auto unix_timestamp = std::chrono::seconds(std::time(nullptr));
    //int last_seen = unix_timestamp - 1200;
    //std::string lastSql = fmt::format("SELECT COUNT(DISTINCT session.username)
FROM session INNER JOIN user ON session.username = user.username "
    //                                  "WHERE session.expire > 1 and
user.last_seen > 2"); return count;
}
*/

void User::get_valid_users() {
  std::string sql = fmt::format("SELECT id FROM user WHERE disabled = false");
  auto db_results = Dba::read(sql);
  for (auto r : db_results) {
  }
}

// User User::get_from_username(std::string username)
//{

//}

// User User::get_from_apikey(std::string apikey)
//{

//}

bool User::is_logged_in() {
  // auto sql = "SELECT id,ip FROM session WHERE username=1 AND expire > now()";
  return context->sessionId() != 0;
}
std::string User::get_password() {
  auto sql = "SELECT * FROM music.user WHERE id = $1";
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    auto r = Dba::writeInTrans(transPtr, sql, this->context->getUserId());
    if (r.size() == 1) {
      return r[0]["password"].as<std::string>();
    }
  } catch (const std::exception& e) {
    SPDLOG_TRACE(e.what());
  }
  return "";
}

long User::create(const std::string& /*username*/,
                  const std::string& /*fullname*/, const std::string& /*email*/,
                  const std::string& /*website*/,
                  const std::string& /*password*/,
                  const std::string& /*access*/, const std::string& /*state*/,
                  const std::string& /*city*/, bool /*disabled*/) {
  // website     = rtrim(website, "/");
  // string password    = hash('sha256', password);
  // bool disabled    = disabled $ 1 : 0;

  /* Now Insert this new user */
  /* Great Logic..
  string sql = "INSERT INTO music.user (username, disabled, fullname, email,
  password, access, create_date"; string params = array(username, disabled,
  fullname, email, password, access, time());

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
  // self::fix_preferences(insert_id);

  // return insert_id;
  return 0;
}

bool User::update_password(std::string new_password) {
  // std::string new_password = hash('sha256', new_password);
  // new_password = Dba::escape(new_password);
  std::string sql = "UPDATE music.user SET password = $2 WHERE id = $1";
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    auto r = Dba::writeInTrans(transPtr, sql, this->context->getUserId(),
                               std::move(new_password));
    if (r.affectedRows() == 1) {
      return true;
    }
    // todo: save updated password in cache...
  } catch (const std::exception& e) {
    SPDLOG_TRACE(e.what());
  }
  return false;
}

nlohmann::json User::userRegister(const nlohmann::json& event,
                                  nlohmann::json args) {
  std::string strSql =
      "INSERT INTO entity.entity ( entity_type_id, no, legal_name, slug, "
      "email) values($1, $2, $3, $4, $5) returning id";
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();

    auto data = args["legal_name"].get<std::string>();
    std::transform(data.begin(), data.end(), data.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    std::transform(data.begin(), data.end(), data.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    std::transform(data.begin(), data.end(), data.begin(),
                   [](char ch) { return ch == ' ' ? '_' : ch; });

    auto x = Dba::writeInTrans(transPtr, strSql, 6, "",
                               args["legal_name"].get<std::string>(), data,
                               args["email"].get<std::string>());
    auto entity_id = x[0]["id"].as<long>();
    std::string strSqlUser =
        "INSERT INTO entity.entity_user (entity_id, username, password, "
        "password_hash) VALUES ($1, $2, $3, $4)";
    Dba::writeInTrans(
        transPtr, strSqlUser, entity_id, args["email"].get<std::string>(),
        args["pass"].get<std::string>(), args["pass"].get<std::string>());

    // websocket::WsFns::successJsonObject(event, true, "Done");
    return userLogin(event, args);
  } catch (const std::exception& e) {
    SPDLOG_TRACE(e.what());
    nlohmann::json ret;
    ret[0] = websocket::WsFns::successJsonObject(event, false, e.what());
    return ret;
  }
}

nlohmann::json User::userLogin(const nlohmann::json& event,
                               nlohmann::json args) {
  auto sql =
      "select e.id from entity.entity e left join entity.entity_user as u on "
      "u.entity_id = e.id where e.email = $1 and u.password = $2";
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    auto r = Dba::writeInTrans(transPtr, sql, args["email"].get<std::string>(),
                               args["pass"].get<std::string>());

    if (r.size() == 1) {
      nlohmann::json j;
      j["value"] = r[0]["id"].as<long>();
      auto sqlSession =
          "INSERT INTO entity.session (key, value) VALUES ($1, $2) returning id";
      // To serialize the nlohmann::json into a Json document, you should use a
      // Json writer, or json::dump().
      LOG_INFO << j.dump();
      auto rs = Dba::writeInTrans(transPtr, sqlSession, "user", j.dump());
      nlohmann::json login_result =
          websocket::WsFns::successJsonObject(event, true, "Done");

      // ask to save cookie
      nlohmann::json cookie_result;
      nlohmann::json cookie_event;
      cookie_event[0] = "auth";
      cookie_event[1] = "set_cookie";
      cookie_event[2] = 0;  // must be zero
      cookie_result[0] = cookie_event;
      nlohmann::json cookie_value;
      // auto s = get_serial_no();
      cookie_value["user"] = rs[0]["id"].as<long>();
      cookie_result[1] = cookie_value;

      context->setSessionId(rs[0]["id"].as<long>());
      nlohmann::json final;
      final[0] = login_result;
      final[1] = cookie_result;
      return final;
    }
    nlohmann::json ret;
    ret[0] = websocket::WsFns::successJsonObject(event, false, "Error");
    return ret;

  } catch (const std::exception& e) {
    SPDLOG_TRACE(e.what());
    nlohmann::json ret;
    ret[0] = websocket::WsFns::successJsonObject(event, false, e.what());
    return ret;
  }
}

nlohmann::json User::userId(const nlohmann::json& event,
                            const nlohmann::json&) {
  long c = context->sessionId();
  if (c != 0) {
    auto sqlSession = "SELECT key, value FROM entity.session where id = $1";
    try {
      auto clientPtr = drogon::app().getDbClient("sce");
      auto transPtr = clientPtr->newTransaction();
      auto r = Dba::writeInTrans(transPtr, sqlSession, c);
      // send id
      // websocket::WsFns::successJsonObject(event, true, r[0][1].c_str());
      nlohmann::json jresult;
      jresult[0] = event;

      try {
        auto root = nlohmann::json::parse(r[0][1].c_str());
        jresult[1] = root["value"];
      } catch (nlohmann::json::parse_error& e) {
        jresult[1] = 0;
        SPDLOG_TRACE("message: {}", e.what());
        SPDLOG_TRACE("exception id: {}", e.id);
        SPDLOG_TRACE("byte position of error:", e.byte);
        nlohmann::json j = std::string("cant parse json reason: ") + e.what();
      }
      return jresult;
    } catch (const std::exception& e) {
      SPDLOG_TRACE(e.what());
      nlohmann::json jresult;
      jresult[0] = event;
      jresult[1] = 0;
      return jresult;
    }
  }
  nlohmann::json ret;
  ret[0] = 0;
  return ret;
}
nlohmann::json User::checkout(const nlohmann::json& event,
                              const nlohmann::json& /*args*/) {
  long c = context->sessionId();
  if (c != 0) {
    auto sqlSession = "SELECT key, value FROM entity.session where id = $1";
    try {
      auto clientPtr = drogon::app().getDbClient("sce");
      auto transPtr = clientPtr->newTransaction();
      auto r = Dba::writeInTrans(transPtr, sqlSession, c);
      // send id
      nlohmann::json jresult;
      jresult[0] = event;

      auto root = nlohmann::json::parse(r[0][1].c_str());
      jresult[1] = root["value"];
      return jresult;
    } catch (const std::exception& e) {
      SPDLOG_TRACE(e.what());
      nlohmann::json jresult;
      jresult[0] = event;
      jresult[1] = 0;
      return jresult;
    }
  } else {
    nlohmann::json ret;
    return ret;
  }
}
}  // namespace jadmin
