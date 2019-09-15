#include "post.h"

#include <utility>
#include "../../../sql/dba.h"
#include "../../../strfns.h"

namespace jadmin {
Post1::Post1(std::shared_ptr<websocket::jadmin::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("post", "post", "post"));
  setupTable();
}

nlohmann::json Post1::handleEvent(nlohmann::json event, unsigned long next,
                                  nlohmann::json args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "data") {
    return query.allData(event, args);
  }
  if (event_cmp == "header") {
    return query.headerData(event, args);
  } else if (event_cmp == "ins") {
    return ins(event, args);
  } else if (event_cmp == "upd") {
    return upd(event, args);
  } else if (event_cmp == "del") {
    return query.del(event, args);
  } else {
    nlohmann::json ret;
    return ret;
  }
}

void Post1::setupTable() {
  query.setSelectedColumns({
      sql::SelectedColumn({"Id", "id", "", "post", sql::PG_TYPES::INT8, true}),
      sql::SelectedColumn(
          {"Post Type", "type", "", "post", sql::PG_TYPES::ENUM, true}),
      sql::SelectedColumn(
          {"Visibility", "visibility", "", "post", sql::PG_TYPES::ENUM, true}),
      sql::SelectedColumn(
          {"Title", "title", "", "post", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Slug", "name", "", "post", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Product_short_description", "excerpt", "", "post",
                           sql::PG_TYPES::TEXT, false}),
      sql::SelectedColumn({"Product_Content", "content", "", "post",
                           sql::PG_TYPES::TEXT, false}),
      sql::SelectedColumn(
          {"Position", "menu_order", "", "post", sql::PG_TYPES::INT8, true}),
      sql::SelectedColumn(
          {"Date", "date", "", "post", sql::PG_TYPES::TIMESTAMP, true}),
      sql::SelectedColumn(
          {"Status", "status", "", "post", sql::PG_TYPES::ENUM, true}),
      sql::SelectedColumn(
          {"Comment", "comment_status", "", "post", sql::PG_TYPES::BOOL, true}),
      sql::SelectedColumn(
          {"Password", "password", "", "post", sql::PG_TYPES::TEXT, false}),
      sql::SelectedColumn(
          {"Modified", "modified", "", "post", sql::PG_TYPES::TIMESTAMP, true}),
      // sql::SelectedColumn({"Parent", "parent", "", "post",
      // sql::PG_TYPES::INT8, true}), sql::SelectedColumn({"MIME Type",
      // "post_mime_type", "", "post", sql::PG_TYPES::ENUM, false}),
      sql::SelectedColumn({"Comment Count", "comment_count", "", "post",
                           sql::PG_TYPES::INT8, true}),
  });
}

nlohmann::json Post1::ins(nlohmann::json event, nlohmann::json args) {
  auto post_table = sql::ObjectIdentifier("post", "post", "p");

  std::string strSqlPost =
      "INSERT INTO %1.%2 "
      "(comment_status, menu_order, excerpt, content, title, name, password, "
      "status, date, type, visibility)"
      " VALUES($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11)"
      "RETURNING id";
  ReplaceAll2(strSqlPost, "%1", post_table.schema());
  ReplaceAll2(strSqlPost, "%2", post_table.name());

  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  try {
    auto x = sql::Dba::writeInTrans(
        transPtr, strSqlPost, args[0]["comment_status"].get<bool>(),
        args[0]["menu_order"].get<int>(), args[0]["excerpt"].get<std::string>(),
        args[0]["content"].get<std::string>(),
        args[0]["title"].get<std::string>(), args[0]["name"].get<std::string>(),
        args[0]["password"].get<std::string>(),
        args[0]["status"].get<std::string>(),
        args[0]["date"].get<std::string>(), args[0]["type"].get<std::string>(),
        args[0]["visibility"].get<std::string>());
    // auto post_id = x[0]["id"].as<long>();

    // product_tags_process(tags_table, post_tag_table, in, txn, post_id);
    // save_product_categories(post_category_table, in, txn, post_id);

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
nlohmann::json Post1::upd(nlohmann::json event, nlohmann::json args) {
  auto post_table = sql::ObjectIdentifier("post", "post", "p");

  if (args[0]["id"].get<long>()) {
    std::string strSqlPost =
        "update %1.%2 set "
        "(comment_status, menu_order, excerpt, content, title, name, password, "
        "status, date, type, visibility)"
        " = ROW($2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12) where id=$1";
    ReplaceAll2(strSqlPost, "%1", post_table.schema());
    ReplaceAll2(strSqlPost, "%2", post_table.name());

    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
      sql::Dba::writeInTrans(transPtr, strSqlPost, args[0]["id"].get<long>(),
                             args[0]["comment_status"].get<bool>(),
                             args[0]["menu_order"].get<int>(),
                             args[0]["excerpt"].get<std::string>(),
                             args[0]["content"].get<std::string>(),
                             args[0]["title"].get<std::string>(),
                             args[0]["name"].get<std::string>(),
                             args[0]["password"].get<std::string>(),
                             args[0]["status"].get<std::string>(),
                             args[0]["date"].get<std::string>(),
                             args[0]["type"].get<std::string>(),
                             args[0]["visibility"].get<std::string>());
      // auto post_id = args[0]["id"].get<long>();

      // product_tags_process(tags_table, post_tag_table, in, txn, post_id);
      // save_product_categories(post_category_table, in, txn, post_id);

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
  nlohmann::json ret;
  ret[0] =
      websocket::WsFns::successJsonObject(event, false, "Not Valid Structure");
  return ret;
}
}  // namespace jadmin
