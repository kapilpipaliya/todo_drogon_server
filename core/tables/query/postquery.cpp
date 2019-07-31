#include "postquery.h"


    void query_post(Table &t) {
    t.m_table = sqlb::ObjectIdentifier("post", "post", "post");
    t.m_query = sqlb::Query(t.m_table);

        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "post", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Post Type", "post_type", "", "post", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Visibility", "visibility", "", "post", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Title", "post_title", "", "post", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Slug", "post_name", "", "post", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Product_short_description", "post_excerpt", "", "post", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Product_Content", "post_content", "", "post", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Position", "menu_order", "", "post", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Date", "post_date", "", "post", PG_TYPES::TIMESTAMP, true}),
            sqlb::SelectedColumn({"Status", "post_status", "", "post", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Comment", "comment_status", "", "post", PG_TYPES::BOOL, true}),
            sqlb::SelectedColumn({"Password", "post_password", "", "post", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Modified", "post_modified", "", "post", PG_TYPES::TIMESTAMP, true}),
            //sqlb::SelectedColumn({"Parent", "post_parent", "", "post", PG_TYPES::INT8, true}),
            //sqlb::SelectedColumn({"MIME Type", "post_mime_type", "", "post", PG_TYPES::ENUM, false}),
            sqlb::SelectedColumn({"Comment Count", "comment_count", "", "post", PG_TYPES::INT8, true}),
            };
}

    void query_tag(Table &t) {

        t.m_table = sqlb::ObjectIdentifier("post", "tag", "t");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "t", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Slug", "slug", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Description", "description", "", "t", PG_TYPES::TEXT, true}),
            //sqlb::SelectedColumn({"Created By", "create_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Create Time", "inserted_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            //sqlb::SelectedColumn({"Update Time", "updated_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto m = sqlb::ObjectIdentifier("material", "metal", "m");
    //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //sqlb::Join("left", m, "a.material_id = m.id"),
            // sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
            // sqlb::Join("left", u2, "a.update_user_id = u2.id"),
            };
}
