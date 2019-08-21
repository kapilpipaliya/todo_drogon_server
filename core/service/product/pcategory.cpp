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

Json::Value PCategory::ins( Json::Value event, Json::Value args)
{
    printJson(args);
    auto product_table = sqlb::ObjectIdentifier("product", "category", "p");

    std::string strSql = "INSERT INTO %1.%2 (slug, name, description, display_type, parent_id, position) values($1, $2, $3, $4, NULLIF($5, 0), $6)";
    ReplaceAll2(strSql, "%1", product_table.schema());
    ReplaceAll2(strSql, "%2", product_table.name());

    auto transPtr = clientPtr->newTransaction();
    try {
        transPtr->execSqlSync(
            strSql,
            args["slug"].asString(),
            args["name"].asString(),
            args["description"].asString(),
            args["display_type"].asString(),
            args["parent_id"].asInt(),
            args["position"].asInt()
            );
        
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }

}
Json::Value PCategory::upd( Json::Value event, Json::Value args)
{
    auto product_table = sqlb::ObjectIdentifier("product", "category", "p");

    if (args["id"].asInt()) {
        std::string strSql =
                "update %1.%2 set "
                "(slug, name, description, display_type, parent_id, position)"
                " = ROW($2, $3, $4, $5, NULLIF($6, 0), $7) where id=$1";
        ReplaceAll2(strSql, "%1", product_table.schema());
        ReplaceAll2(strSql, "%2", product_table.name());


        try {
            clientPtr->execSqlSync(strSql,
                                   args["id"].asInt64(),
                    args["slug"].asString(),
                    args["name"].asString(),
                    args["description"].asString(),
                    args["display_type"].asString(),
                    args["parent_id"].asInt(),
                    args["position"].asInt()
                    );

            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const drogon::orm::DrogonDbException &e) {
            std::cerr << e.base().what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.base().what()); return ret;
        }
    }
}

