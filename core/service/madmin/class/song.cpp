#include "song.h"
using namespace  madmin;
typedef sqlb::SelectedColumn S;
Song::Song(const MAdminContextPtr &context_): BaseService(context_)
{
    t.m_table = sqlb::ObjectIdentifier("music", "song", "s");
    t.m_query = sqlb::Query(t.m_table);
}

void Song::setupTable()
{
    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
            S({"Id", "id", "", "s", PG_TYPES::INT8}),
//            S({"file", "file", "", "s", PG_TYPES::TEXT}),
            S({"Catalog", "catalog_id", "", "s", PG_TYPES::INT8, true, 1, 1}),
            S({"c_name", "name", "", "c", PG_TYPES::TEXT, false, 0, 0, false}),
//            S({"Album", "album_id", "", "s", PG_TYPES::INT8}),
//            S({"Year", "year", "", "s", PG_TYPES::INT4}),
//            S({"Artist", "artist_id", "", "s", PG_TYPES::INT8}),
            S({"Title", "title", "", "s", PG_TYPES::TEXT}),
//            S({"bitrate", "bitrate", "", "s", PG_TYPES::INT4}),
//            S({"rate", "rate", "", "s", PG_TYPES::INT4}),
//            S({"mode", "mode", "", "s", PG_TYPES::ENUM}),
//            S({"size", "size", "", "s", PG_TYPES::INT8}),
//            S({"time", "time", "", "s", PG_TYPES::INT4}),
//            S({"track", "track", "", "s", PG_TYPES::INT4}),
//            S({"mbid", "mbid", "", "s", PG_TYPES::TEXT}),
//            S({"played", "played", "", "s", PG_TYPES::BOOL}),
//            S({"enabled", "enabled", "", "s", PG_TYPES::BOOL}),
//            S({"update_time", "update_time", "", "s", PG_TYPES::TIMESTAMP}),
//            S({"addition_time", "addition_time", "", "s", PG_TYPES::TIMESTAMP}),
//            S({"user_upload", "user_upload", "", "s", PG_TYPES::INT8}),
//            S({"license", "license", "", "s", PG_TYPES::INT8}),
//            S({"composer", "composer", "", "s", PG_TYPES::TEXT}),
//            S({"channels", "channels", "", "s", PG_TYPES::INT4}),

            //S({"no", "no", "", "s", PG_TYPES::TEXT}),
            //S({"sequence_id", "sequence_id", "", "s", PG_TYPES::INT8, false}),
            //S({"Create Date", "last_update", "", "s", PG_TYPES::TIMESTAMP}),
            //S({"last_clean Date", "last_clean", "", "s", PG_TYPES::TIMESTAMP}),
            //S({"last_add Date", "last_add", "", "s", PG_TYPES::TIMESTAMP}),
            //S({"Rename Pattern", "rename_pattern", "", "s", PG_TYPES::TEXT, true}),
            //S({"Sort Pattern", "sort_pattern", "", "s", PG_TYPES::TEXT, true}),
            //S({"Gather Types", "gather_types", "", "s", PG_TYPES::TEXT, true}),
            //S({"Created By", "create_user_id", "", "s", PG_TYPES::INT8, true, 1, 0, false}), S({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //S({"Updated By", "update_user_id", "", "s", PG_TYPES::INT8, true, 1, 0, false}), S({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            //S({"Create Time", "inserted_at", "", "s", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            //S({"Update Time", "updated_at", "", "s", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
    };
    auto c = sqlb::ObjectIdentifier("music", "catalog", "c");
    //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", c, "c.id = s.catalog_id")
            //sqlb::Join("left", u1, "e.create_user_id = u1.id"),
            //sqlb::Join("left", u2, "e.update_user_id = u2.id"),
            };

    t.m_query.groupBy() = {
        };
}

nlohmann::json Song::handleEvent(nlohmann::json event, unsigned long next, nlohmann::json args)
{
    auto event_cmp = event[next].get<std::string>();
    if (event_cmp == "header") { // required
        return headerData(event, args);
    } else if (event_cmp == "data") { // required
        //if(context->user.type == "super admin"){
            return allData(event, args);
        //} else {
            //return {{event, "unauthorised"}};
        //}
    } else if (event_cmp  == "ins") {
        //args[0]["parent_id"] = context->user_id;
        return ins(event, args);
    } else if (event_cmp  == "upd") {
        return upd(event, args);
    } else if (event_cmp  == "del") {
        return del(event, args);
    } else if (event_cmp  == "count") {
        return count(event, args);
    } else {
        return nullptr;
    }
}
