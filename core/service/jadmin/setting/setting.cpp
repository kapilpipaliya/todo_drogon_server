#include "setting.h"

#include <utility>
#include "../../dba.h"
using namespace jadmin;

Setting::Setting(JAdminContextPtr context_) : context(std::move(context_)) {
  getTable().query() =
      sqlb::Query(sqlb::ObjectIdentifier("setting", "setting", "gs"));
}

json Setting::handleEvent(json event, int next, const json &args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "data") {
    return allData(event, args);
  }
  if (event_cmp == "header") {
    return headerData(event, args);
  } else if (event_cmp == "save") {
    return save(event, args);
  } else if (event_cmp == "del") {
    return del(event, args);
  } else {
    json ret;
    return ret;
  }
}

void Setting::setupTable() {
  // m_query.setRowIdColumn("id");
  getTable().query().selectedColumns() = {
      sqlb::SelectedColumn({"Key", "key", "", "gs", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Setting Type", "setting_type", "", "gs", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Integer", "value_int", "", "gs", PG_TYPES::INT8, true}),
      sqlb::SelectedColumn(
          {"Decimal", "value_num", "", "gs", PG_TYPES::DOUBLE, true}),
      sqlb::SelectedColumn(
          {"Text", "value_text", "", "gs", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Internal", "setting", "", "gs", PG_TYPES::PSJSON, true}),
  };
  // auto m = sqlb::ObjectIdentifier("material", "metal", "m");
  // auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  // auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");
  getTable().query().joins() = {
      // sqlb::Join("left", m, "a.material_id = m.id"),
      // sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
      // sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  };
}

// where key = $1
json Setting::del(json event, json args) {
  // to support global filter, get first all ids b selected filter and for each
  // id delete.
  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  try {
    auto res = Dba::writeInTrans(transPtr,
                                 "DELETE FROM setting.setting WHERE key = $1",
                                 args[0][0].get<std::string>());
    if (res.size() > 1) {
      throw("not valid arguments");
    }
    json ret;
    ret[0] = simpleJsonSaveResult(event, true, "Done");
    return ret;
  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    json ret;
    ret[0] = simpleJsonSaveResult(event, false, e.what());
    return ret;
  }
}
json Setting::save(const json &event, json args) {
  // check if key exist
  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  auto key = args[0]["key"].get<std::string>();
  auto y = Dba::writeInTrans(
      transPtr, "select key from setting.setting where key = $1", key);

  if (!y.empty()) {
    std::string strSql =
        "update setting.setting set (value_int, value_num, value_text) = "
        "ROW($2, $3, $4) where key=$1";
    try {
      Dba::writeInTrans(transPtr, strSql, args[0]["key"].get<std::string>(),
                        args[0]["value_int"].get<int>(),
                        args[0]["value_num"].get<float>(),
                        args[0]["value_text"].get<std::string>());

      json ret;
      ret[0] = simpleJsonSaveResult(event, true, "Done");
      return ret;
    } catch (const std::exception &e) {
      SPDLOG_TRACE(e.what());
      json ret;
      ret[0] = simpleJsonSaveResult(event, false, e.what());
      return ret;
    }
  } else {
    std::string strSql =
        "INSERT INTO setting.setting (key, value_int, value_num, value_text, "
        "setting_type, setting) values($1, $2, $3, $4, $5, $6)";
    try {
      Dba::writeInTrans(transPtr, strSql, args[0]["key"].get<std::string>(),
                        args[0]["value_int"].get<int>(),
                        args[0]["value_num"].get<float>(),
                        args[0]["value_text"].get<std::string>(),
                        args[0]["setting_type"].get<std::string>(),
                        args[0]["setting"].dump());

      json ret;
      ret[0] = simpleJsonSaveResult(event, true, "Done");
      return ret;
    } catch (const std::exception &e) {
      SPDLOG_TRACE(e.what());
      json ret;
      ret[0] = simpleJsonSaveResult(event, false, e.what());
      return ret;
    }
  }
}
