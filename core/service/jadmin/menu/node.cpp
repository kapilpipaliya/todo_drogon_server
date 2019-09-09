#include "node.h"

#include <utility>

namespace jadmin {
Node::Node(std::shared_ptr<JAdminContext> context_) : context(std::move(context_)) {
  query = sqlb::Query(sqlb::ObjectIdentifier("menu", "node", "m"));
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
      sqlb::SelectedColumn({"Id", "id", "", "m", PG_TYPES::INT8, true}),
      sqlb::SelectedColumn(
          {"Parent", "parent_id", "", "m", PG_TYPES::INT4, true}),
      sqlb::SelectedColumn({"Rank", "rank", "", "m", PG_TYPES::INT4, true}),
      sqlb::SelectedColumn({"Code", "slug", "", "m", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn({"Label", "label", "", "m", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn({"Active", "active", "", "m", PG_TYPES::BOOL, true}),
      sqlb::SelectedColumn({"Url", "url", "", "m", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Web Icon", "web_icon", "", "m", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Description", "description", "", "m", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn({"Class", "class", "", "m", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Created By", "create_user_id", "", "m", PG_TYPES::INT8, true, 1}),
      sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      sqlb::SelectedColumn(
          {"Updated By", "update_user_id", "", "m", PG_TYPES::INT8, true, 1}),
      sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      sqlb::SelectedColumn({"Create Time", "inserted_at", "", "m",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sqlb::SelectedColumn({"Update Time", "updated_at", "", "m",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({

      sqlb::Join("left", u1, "m.create_user_id = u1.id"),
      sqlb::Join("left", u2, "m.update_user_id = u2.id"),
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
}  // namespace jadmin
