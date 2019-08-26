#include "node.h"
#include "../../../strfns.h"
#include "../../../jsonfns.h"

Node::Node()
{

    t.m_table = sqlb::ObjectIdentifier("menu", "node", "m");
}

void Node::setupTable()
{
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "m", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Parent", "parent_id", "", "m", PG_TYPES::INT4, true}),
            sqlb::SelectedColumn({"Rank", "rank", "", "m", PG_TYPES::INT4, true}),
            sqlb::SelectedColumn({"Code", "slug", "", "m", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Label", "label", "", "m", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Active", "active", "", "m", PG_TYPES::BOOL, true}),
            sqlb::SelectedColumn({"Url", "url", "", "m", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Web Icon", "web_icon", "", "m", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Description", "description", "", "m", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Class", "class", "", "m", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "m", PG_TYPES::INT8, true, 1}),
            sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "m", PG_TYPES::INT8, true, 1}),
            sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "m", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "m", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };


        auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {

            sqlb::Join("left", u1, "m.create_user_id = u1.id"),
            sqlb::Join("left", u2, "m.update_user_id = u2.id"),
            };
}

json Node::ins(json event, json args)
{
    return insBase(event, args, "parent_id, rank, slug, label, active, url, web_icon, description, class", "$1,$2,$3,$4,$5,$6,$7,$8,$9",
            args[0]["parent_id"].get<long>(),
            args[0]["rank"].get<int>(),
            args[0]["slug"].get<std::string>(),
            args[0]["label"].get<std::string>(),
            args[0]["active"].get<bool>(),
            args[0]["url"].get<std::string>(),
            args[0]["web_icon"].get<std::string>(),
            args[0]["description"].get<std::string>(),
            args[0]["class"].get<std::string>()
            );
}

json Node::upd(json event, json args)
{
    return updBase(event, args, "parent_id, rank, slug, label, active, url, web_icon, description, class", "$1,$2,$3,$4,$5,$6,$7,$8,$9",
                args[0]["parent_id"].get<long>(),
                args[0]["rank"].get<int>(),
                args[0]["slug"].get<std::string>(),
                args[0]["label"].get<std::string>(),
                args[0]["active"].get<bool>(),
                args[0]["url"].get<std::string>(),
                args[0]["web_icon"].get<std::string>(),
                args[0]["description"].get<std::string>(),
                args[0]["class"].get<std::string>());
}