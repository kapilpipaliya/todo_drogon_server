#include "journaltype.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

JournalType::JournalType(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{
    t.m_table = sqlb::ObjectIdentifier("account", "journal_type", "a");

}

    void JournalType::setupTable()
{
        t.m_query = sqlb::Query(t.m_table);

            //m_query.setRowIdColumn("id");
            t.m_query.selectedColumns() = {
                sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, true}),
                sqlb::SelectedColumn({"Rank", "rank", "", "a", PG_TYPES::INT4, false}),
                sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
                sqlb::SelectedColumn({"Description", "description", "", "a", PG_TYPES::TEXT, true}),
                sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
                sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
                sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
                sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
                sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
                sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
                };

            auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
        auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

            t.m_query.joins() = {
                sqlb::Join("left", u1, "a.create_user_id = u1.id"),
                sqlb::Join("left", u2, "a.update_user_id = u2.id"),
                };
}
Json::Value JournalType::ins(Json::Value event, Json::Value args)
{
    return insBase(event, args, "rank, name, description", "$1, $2, $3", args[0]["rank"].asInt(), args[0]["name"].asString(), args[0]["description"].asString());
}

Json::Value JournalType::upd(Json::Value event, Json::Value args)
{
    return updBase(event, args, "rank, name, description", "$1, $2, $3", args[0]["rank"].asInt(), args[0]["name"].asString(), args[0]["description"].asString());
}
