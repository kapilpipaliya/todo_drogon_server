#include "post.h"
#include "../../dba.h"
#include "../../../strfns.h"
using namespace  jadmin;

Post1::Post1(const JAdminContextPtr &context_): context(context_)
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


json Post1::ins( json event, json args) {
    auto post_table = sqlb::ObjectIdentifier("post", "post", "p");

    std::string strSqlPost =
        "INSERT INTO %1.%2 "
        "(comment_status, menu_order, excerpt, content, title, name, password, status, date, type, visibility)"
        " VALUES($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11)"
        "RETURNING id";
    ReplaceAll2(strSqlPost, "%1", post_table.schema());
    ReplaceAll2(strSqlPost, "%2", post_table.name());

    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
        auto x = Dba::writeInTrans(transPtr, 
            strSqlPost,
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
            args[0]["visibility"].get<std::string>()
            );
        //auto post_id = x[0]["id"].as<long>();

        //product_tags_process(tags_table, post_tag_table, in, txn, post_id);
        //save_product_categories(post_category_table, in, txn, post_id);

        
        json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        
       SPDLOG_TRACE(e.what());
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
json Post1::upd( json event, json args) {
    auto post_table = sqlb::ObjectIdentifier("post", "post", "p");

    if (args[0]["id"].get<long>()) {
        std::string strSqlPost =
                "update %1.%2 set "
                "(comment_status, menu_order, excerpt, content, title, name, password, status, date, type, visibility)"
                " = ROW($2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12) where id=$1";
        ReplaceAll2(strSqlPost, "%1", post_table.schema());
        ReplaceAll2(strSqlPost, "%2", post_table.name());

        auto clientPtr = drogon::app().getDbClient("sce");
        auto transPtr = clientPtr->newTransaction();
        try {
            Dba::writeInTrans(transPtr, strSqlPost,
                            args[0]["id"].get<long>(),
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
                    args[0]["visibility"].get<std::string>()
                    );
            //auto post_id = args[0]["id"].get<long>();

            //product_tags_process(tags_table, post_tag_table, in, txn, post_id);
            //save_product_categories(post_category_table, in, txn, post_id);

            
            json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            
           SPDLOG_TRACE(e.what());
            json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
    json ret; ret[0] = simpleJsonSaveResult(event, false, "Not Valid Structure"); return ret;
}
