#include "setting.h"

#include <utility>
#include "../../../sql/dba.h"

namespace jadmin {
namespace service {
Setting::Setting(std::shared_ptr<websocket::jadmin::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("entity", "setting", "gs"));
  setupTable();
}

nlohmann::json Setting::handleEvent(nlohmann::json event, unsigned long next,
                                    nlohmann::json args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "data") {
    return query.allData(event, args);
  }
  if (event_cmp == "header") {
    return query.headerData(event, args);
  } else if (event_cmp == "save" || event_cmp == "ins" || event_cmp == "upd") {
    return save(event, args);
  } else if (event_cmp == "del") {
    return del(event, args);
  } else {
    nlohmann::json ret;
    return ret;
  }
}

void Setting::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sql::SelectedColumn({"Key", "key", "", "gs", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Setting Type", "setting_type", "", "gs",
                           sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Integer", "value_int", "", "gs", sql::PG_TYPES::INT8, true}),
      sql::SelectedColumn(
          {"Decimal", "value_num", "", "gs", sql::PG_TYPES::DOUBLE, true}),
      sql::SelectedColumn(
          {"Text", "value_text", "", "gs", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Internal", "setting", "", "gs", sql::PG_TYPES::PSJSON, true}),
  });
  // auto m = sql::ObjectIdentifier("material", "metal", "m");
  // auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  // auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");
  query.setJoins({
      // sql::Join("left", m, "a.material_id = m.id"),
      // sql::Join("left", u1, "gt.create_user_id = u1.id"),
      // sql::Join("left", u2, "a.update_user_id = u2.id"),
  });
}

// where key = $1
nlohmann::json Setting::del(nlohmann::json event, nlohmann::json args) {
  // to support global filter, get first all ids b selected filter and for each
  // id delete.
  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  try {
    auto res = sql::Dba::writeInTrans(
        transPtr, "DELETE FROM entity.setting WHERE key = $1",
        args[0][0].get<std::string>());
    if (res.size() > 1) {
      throw std::runtime_error("not valid arguments");
    }
    nlohmann::json ret;
    ret[0] = websocket::WsFns::successJsonObject(event, true, "Done");
    return ret;
  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    nlohmann::json ret;
    ret[0] = websocket::WsFns::successJsonObject(event, false, e.what());
    return ret;
  }
}
nlohmann::json Setting::save(const nlohmann::json &event, nlohmann::json args) {
  // check if key exist
  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  auto key = args[0]["key"].get<std::string>();
  auto y = sql::Dba::writeInTrans(
      transPtr, "select key from entity.setting where key = $1", key);
  auto int_value =
      !args[0]["value_int"].is_null() ? args[0]["value_int"].get<int>() : 0;
  auto float_value =
      !args[0]["value_num"].is_null() ? args[0]["value_num"].get<float>() : 0;
  auto string_value = !args[0]["value_text"].is_null()
                          ? args[0]["value_text"].get<std::string>()
                          : "";
  if (!y.empty()) {
    std::string strSql =
        "update entity.setting set (value_int, value_num, value_text) = "
        "ROW($2, $3, $4) where key=$1";
    try {
      sql::Dba::writeInTrans(transPtr, strSql,
                             args[0]["key"].get<std::string>(), int_value,
                             float_value, string_value);

      nlohmann::json ret;
      ret[0] = websocket::WsFns::successJsonObject(event, true, "Done");
      return ret;
    } catch (const std::exception &e) {
      SPDLOG_TRACE(e.what());
      nlohmann::json ret;
      ret[0] = websocket::WsFns::successJsonObject(event, false, e.what());
      return ret;
    }
  } else {
    std::string strSql =
        "INSERT INTO entity.setting (key, value_int, value_num, value_text, "
        "setting_type, setting) values($1, $2, $3, $4, $5, $6)";
    try {
      sql::Dba::writeInTrans(
          transPtr, strSql, args[0]["key"].get<std::string>(), int_value,
          float_value, string_value, args[0]["setting_type"].get<std::string>(),
          nlohmann::json::object().dump());

      nlohmann::json ret;
      ret[0] = websocket::WsFns::successJsonObject(event, true, "Done");
      return ret;
    } catch (const std::exception &e) {
      SPDLOG_TRACE(e.what());
      nlohmann::json ret;
      ret[0] = websocket::WsFns::successJsonObject(event, false, e.what());
      return ret;
    }
  }
}
}  // namespace service
}  // namespace jadmin
