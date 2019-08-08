#include "postsave.h"

delFn(post, "post.post");

delFn(tag, "post.tag");

Json::Value save_post(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    auto post_table = sqlb::ObjectIdentifier("post", "post", "p");

    if (in["id"].asInt()) {
        std::string strSqlPost =
            "update %1.%2 set "
            "(comment_status, menu_order, excerpt, content, title, name, password, status, date, type, visibility)"
            " = ROW($2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12) where id=$1";
        ReplaceAll2(strSqlPost, "%1", post_table.schema());
        ReplaceAll2(strSqlPost, "%2", post_table.name());

        pqxx::work txn{DD};
        try {
            txn.exec_params(strSqlPost,
                            in["id"].asInt(),
                            in["comment_status"].asBool(),
                            in["menu_order"].asInt(),
                            in["excerpt"].asString(),
                            in["content"].asString(),
                            in["title"].asString(),
                            in["name"].asString(),
                            in["password"].asString(),
                            in["status"].asString(),
                            in["date"].asString(),
                            in["type"].asString(),
                            in["visibility"].asString()
                            );
            auto post_id = in["id"].asInt();

            //product_tags_process(tags_table, post_tag_table, in, txn, post_id);
            //save_product_categories(post_category_table, in, txn, post_id);

            txn.commit();
            return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
        }
    } else {
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
                in["comment_status"].asBool(),
                in["menu_order"].asInt(),
                in["excerpt"].asString(),
                in["content"].asString(),
                in["title"].asString(),
                in["name"].asString(),
                in["password"].asString(),
                in["status"].asString(),
                in["date"].asString(),
                in["type"].asString(),
                in["visibility"].asString()
                );
            auto post_id = x[0]["id"].as<int>();

            //product_tags_process(tags_table, post_tag_table, in, txn, post_id);
            //save_product_categories(post_category_table, in, txn, post_id);

            txn.commit();
            return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
        }
    }
}

Json::Value save_tag(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    printJson(in);
    auto product_table = sqlb::ObjectIdentifier("post", "tag", "t");

    if (in["id"].asInt()) {
        std::string strSql =
            "update %1.%2 set "
            "(slug, name, description)"
            " = ROW($2, $3, $4) where id=$1";
        ReplaceAll2(strSql, "%1", product_table.schema());
        ReplaceAll2(strSql, "%2", product_table.name());

        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql,
                            in["id"].asInt(),
                            in["slug"].asString(),
                            in["name"].asString(),
                            in["description"].asString()
                            );
            txn.commit();
            return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
        }
    } else {
        std::string strSql = "INSERT INTO %1.%2 (slug, name, description) values($1, $2, $3)";
        ReplaceAll2(strSql, "%1", product_table.schema());
        ReplaceAll2(strSql, "%2", product_table.name());

        pqxx::work txn{DD};
        try {
            txn.exec_params(
                strSql,
                in["slug"].asString(),
                in["name"].asString(),
                in["description"].asString()
                );
            txn.commit();
            return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
        }
    }
}
