#include "pcategory.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

PCategory::PCategory(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{
    t.m_table = sqlb::ObjectIdentifier("product", "category", "c");
}

void PCategory::setupTable()
{

    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn({"Id", "id", "", "c", PG_TYPES::INT8, false}),
        sqlb::SelectedColumn({"Parent", "parent_id", "", "c", PG_TYPES::INT8, true, 2, 1}),
        sqlb::SelectedColumn({"p_slug", "slug", "", "p", PG_TYPES::TEXT, false, 0, 0, false}),
        sqlb::SelectedColumn({"p_name", "name", "", "p", PG_TYPES::TEXT, false, 0, 0, false}),
        sqlb::SelectedColumn({"Position", "position", "", "c", PG_TYPES::INT8, true}),
        sqlb::SelectedColumn({"Name", "name", "", "c", PG_TYPES::TEXT, true}),
        sqlb::SelectedColumn({"Code", "slug", "", "c", PG_TYPES::TEXT, true}),
        sqlb::SelectedColumn({"Description", "description", "", "c", PG_TYPES::TEXT, true}),
        sqlb::SelectedColumn({"Display Type", "display_type", "", "c", PG_TYPES::TEXT, true}),
        sqlb::SelectedColumn({"Created By", "create_user_id", "", "c", PG_TYPES::INT8, true, 1, 0, false}),
        sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
        sqlb::SelectedColumn({"Updated By", "update_user_id", "", "c", PG_TYPES::INT8, true, 1, 0, false}),
        sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
        sqlb::SelectedColumn({"Create Time", "inserted_at", "", "c", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
        sqlb::SelectedColumn({"Update Time", "updated_at", "", "c", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
        };

    auto p = sqlb::ObjectIdentifier("product", "category", "p");
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

    t.m_query.joins() = {
        sqlb::Join("left", p, "c.parent_id = p.id"),
        sqlb::Join("left", u1, "c.create_user_id = u1.id"),
        sqlb::Join("left", u2, "c.update_user_id = u2.id"),
    };
}

Json::Value PCategory::ins(Json::Value event, Json::Value args)
{
    return insBase(event, args, "slug, name, description, display_type, parent_id, position", "$1, $2, $3, $4, NULLIF($5, 0), $6",
            args["slug"].asString(),
            args["name"].asString(),
            args["description"].asString(),
            args["display_type"].asString(),
            args["parent_id"].asInt(), // why this ask for asInt()? otherwise error: ERROR:  incorrect binary data format in bind parameter 5
            args["position"].asInt64() );
}

Json::Value PCategory::upd(Json::Value event, Json::Value args)
{
    return updBase(event, args, "slug, name, description, display_type, parent_id, position", "$1, $2, $3, $4, NULLIF($5, 0), $6",
                   args[1]["slug"].asString(),
                   args[1]["name"].asString(),
                   args[1]["description"].asString(),
                   args[1]["display_type"].asString(),
                   args[1]["parent_id"].asInt(), // why this ask for asInt()?
                   args[1]["position"].asInt64());
}

