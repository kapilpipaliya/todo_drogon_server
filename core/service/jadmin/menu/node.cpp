#include "node.h"

#include <utility>

namespace jewel {
namespace service {
Node::Node(std::shared_ptr<websocket::jewel::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("menu", "node", "m"));
  setupTable();
}

nlohmann::json Node::handleEvent(nlohmann::json event, unsigned long next,
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

void Node::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sql::SelectedColumn({"Id", "id", "", "m", sql::PG_TYPES::INT8, true}),
      sql::SelectedColumn(
          {"Parent", "parent_id", "", "m", sql::PG_TYPES::INT4, true}),
      sql::SelectedColumn({"Rank", "rank", "", "m", sql::PG_TYPES::INT4, true}),
      sql::SelectedColumn({"Code", "slug", "", "m", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Label", "label", "", "m", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Active", "active", "", "m", sql::PG_TYPES::BOOL, true}),
      sql::SelectedColumn({"Url", "url", "", "m", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Web Icon", "web_icon", "", "m", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Description", "description", "", "m", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Class", "class", "", "m", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Created By", "create_user_id", "", "m",
                           sql::PG_TYPES::INT8, true, 1}),
      sql::SelectedColumn({"u1_username", "username", "", "u1",
                           sql::PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn({"Updated By", "update_user_id", "", "m",
                           sql::PG_TYPES::INT8, true, 1}),
      sql::SelectedColumn({"u2_username", "username", "", "u2",
                           sql::PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn({"Create Time", "inserted_at", "", "m",
                           sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sql::SelectedColumn({"Update Time", "updated_at", "", "m",
                           sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({

      sql::Join("left", u1, "m.create_user_id = u1.id"),
      sql::Join("left", u2, "m.update_user_id = u2.id"),
  });
}

nlohmann::json Node::ins(nlohmann::json event, nlohmann::json args) {
  return query.insBase(
      event, args,
      "parent_id, rank, slug, label, active, url, web_icon, description, class",
      "$1,$2,$3,$4,$5,$6,$7,$8,$9", args[0]["parent_id"].get<long>(),
      args[0]["rank"].get<int>(), args[0]["slug"].get<std::string>(),
      args[0]["label"].get<std::string>(), args[0]["active"].get<bool>(),
      args[0]["url"].get<std::string>(), args[0]["web_icon"].get<std::string>(),
      args[0]["description"].get<std::string>(),
      args[0]["class"].get<std::string>());
}

nlohmann::json Node::upd(nlohmann::json event, nlohmann::json args) {
  return query.updBase(
      event, args,
      "parent_id, rank, slug, label, active, url, web_icon, description, class",
      "$1,$2,$3,$4,$5,$6,$7,$8,$9", args[0]["parent_id"].get<long>(),
      args[0]["rank"].get<int>(), args[0]["slug"].get<std::string>(),
      args[0]["label"].get<std::string>(), args[0]["active"].get<bool>(),
      args[0]["url"].get<std::string>(), args[0]["web_icon"].get<std::string>(),
      args[0]["description"].get<std::string>(),
      args[0]["class"].get<std::string>());
}
}  // namespace service
}  // namespace jadmin
