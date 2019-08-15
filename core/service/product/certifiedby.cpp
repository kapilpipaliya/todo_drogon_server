#include "certifiedby.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

CertifiedBy::CertifiedBy(const WebSocketConnectionPtr& wsConnPtr): wsConnPtr(wsConnPtr)
{

    t.m_table = sqlb::ObjectIdentifier("product", "certified_by", "t");
}

void CertifiedBy::setupTable()
{
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "t", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Title", "title", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Description", "description", "", "t", PG_TYPES::TEXT, true}),
            //        sqlb::SelectedColumn({"Product Count", " "",product_count", "t", PG_TYPES::INT4, true}),
            //sqlb::SelectedColumn({"Created By", "create_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Create Time", "inserted_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            //sqlb::SelectedColumn({"Update Time", "updated_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        //auto m = sqlb::ObjectIdentifier("material", "metal", "m");
        //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
        //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //sqlb::Join("left", m, "t.material_id = m.id"),
            // sqlb::Join("left", u1, "t.create_user_id = u1.id"),
            // sqlb::Join("left", u2, "t.update_user_id = u2.id"),
            };
}

HANDLEEVENT(CertifiedBy)

HEADERDATA(CertifiedBy)
ALLDATA(CertifiedBy)
delFn(CertifiedBy)

    Json::Value CertifiedBy::save( Json::Value event, Json::Value args) {
    auto setting_type_table = sqlb::ObjectIdentifier("product", "certified_by", "s");

    if (args["id"].asInt()) {
        std::string strSql =
            "update %1.%2 set "
            "(slug, name, title, description)"
            " = ROW($2, $3, $4, $5) where id=$1";
        ReplaceAll2(strSql, "%1", setting_type_table.schema());
        ReplaceAll2(strSql, "%2", setting_type_table.name());

        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql,
                            args["id"].asInt(),
                            args["slug"].asString(),
                            args["name"].asString(),
                            args["title"].asString(),
                            args["description"].asString()
                            );
            txn.commit();
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    } else {
        std::string strSql = "INSERT INTO %1.%2 (slug, name, title, description) values($1, $2, $3, $4)";
        ReplaceAll2(strSql, "%1", setting_type_table.schema());
        ReplaceAll2(strSql, "%2", setting_type_table.name());

        pqxx::work txn{DD};
        try {
            txn.exec_params(
                strSql,
                args["slug"].asString(),
                args["name"].asString(),
                args["title"].asString(),
                args["description"].asString()
                );
            txn.commit();
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
}