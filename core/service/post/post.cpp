#include "post.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

Post1::Post1(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{
    t.m_table = sqlb::ObjectIdentifier("post", "post", "post");

}

void Post1::setupTable()
{
    t.m_query = sqlb::Query(t.m_table);

        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "post", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Post Type", "type", "", "post", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Visibility", "visibility", "", "post", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Title", "title", "", "post", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Slug", "name", "", "post", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Product_short_description", "excerpt", "", "post", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Product_Content", "content", "", "post", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Position", "menu_order", "", "post", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Date", "date", "", "post", PG_TYPES::TIMESTAMP, true}),
            sqlb::SelectedColumn({"Status", "status", "", "post", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Comment", "comment_status", "", "post", PG_TYPES::BOOL, true}),
            sqlb::SelectedColumn({"Password", "password", "", "post", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Modified", "modified", "", "post", PG_TYPES::TIMESTAMP, true}),
            //sqlb::SelectedColumn({"Parent", "parent", "", "post", PG_TYPES::INT8, true}),
            //sqlb::SelectedColumn({"MIME Type", "post_mime_type", "", "post", PG_TYPES::ENUM, false}),
            sqlb::SelectedColumn({"Comment Count", "comment_count", "", "post", PG_TYPES::INT8, true}),
            };
}


Json::Value Post1::ins( Json::Value event, Json::Value args) {
    auto post_table = sqlb::ObjectIdentifier("post", "post", "p");

    std::string strSqlPost =
        "INSERT INTO %1.%2 "
        "(comment_status, menu_order, excerpt, content, title, name, password, status, date, type, visibility)"
        " VALUES($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11)"
        "RETURNING id";
    ReplaceAll2(strSqlPost, "%1", post_table.schema());
    ReplaceAll2(strSqlPost, "%2", post_table.name());

    pqxx::work txn{DD};
    try {
        pqxx::result x = txn.exec_params(
            strSqlPost,
            args["comment_status"].asBool(),
            args["menu_order"].asInt(),
            args["excerpt"].asString(),
            args["content"].asString(),
            args["title"].asString(),
            args["name"].asString(),
            args["password"].asString(),
            args["status"].asString(),
            args["date"].asString(),
            args["type"].asString(),
            args["visibility"].asString()
            );
        auto post_id = x[0]["id"].as<int>();

        //product_tags_process(tags_table, post_tag_table, in, txn, post_id);
        //save_product_categories(post_category_table, in, txn, post_id);

        txn.commit();
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
Json::Value Post1::upd( Json::Value event, Json::Value args) {
    auto post_table = sqlb::ObjectIdentifier("post", "post", "p");

    if (args["id"].asInt()) {
        std::string strSqlPost =
                "update %1.%2 set "
                "(comment_status, menu_order, excerpt, content, title, name, password, status, date, type, visibility)"
                " = ROW($2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12) where id=$1";
        ReplaceAll2(strSqlPost, "%1", post_table.schema());
        ReplaceAll2(strSqlPost, "%2", post_table.name());

        pqxx::work txn{DD};
        try {
            txn.exec_params(strSqlPost,
                            args["id"].asInt64(),
                    args["comment_status"].asBool(),
                    args["menu_order"].asInt(),
                    args["excerpt"].asString(),
                    args["content"].asString(),
                    args["title"].asString(),
                    args["name"].asString(),
                    args["password"].asString(),
                    args["status"].asString(),
                    args["date"].asString(),
                    args["type"].asString(),
                    args["visibility"].asString()
                    );
            auto post_id = args["id"].asInt();

            //product_tags_process(tags_table, post_tag_table, in, txn, post_id);
            //save_product_categories(post_category_table, in, txn, post_id);

            txn.commit();
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
}
