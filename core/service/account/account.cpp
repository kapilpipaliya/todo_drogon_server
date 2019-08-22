#include "account.h"
#include "../../strfns.h"
#include "../../jsonfns.h"
Account::Account(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{
    t.m_table = sqlb::ObjectIdentifier("account", "account", "a");
}

    void Account::setupTable()
{

        t.m_query = sqlb::Query(t.m_table);

            //m_query.setRowIdColumn("id");
            t.m_query.selectedColumns() = {
                sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
                sqlb::SelectedColumn({"Material", "material_id", "", "a", PG_TYPES::INT8, true, 1, 2}),
                sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false}),
                sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false}),
                sqlb::SelectedColumn({"Rank", "rank", "", "a", PG_TYPES::INT4, false}),
                sqlb::SelectedColumn({"Code", "slug", "", "a", PG_TYPES::TEXT, true}),
                sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
                sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
                sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
                sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
                sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
                sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
                sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
                };

            auto m = sqlb::ObjectIdentifier("material", "metal", "m");
        auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
        auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

            t.m_query.joins() = {
                sqlb::Join("left", m, "a.material_id = m.id"),
                sqlb::Join("left", u1, "a.create_user_id = u1.id"),
                sqlb::Join("left", u2, "a.update_user_id = u2.id"),
                };
}

    json Account::ins(json event, json args)
    {
        return insBase(event, args, "rank, name, description", "$1, $2, $3", args[0]["rank"].get<int>(), args[0]["name"].get<std::string>(), args[0]["description"].get<std::string>());
    }

    json Account::upd(json event, json args)
    {
        return updBase(event, args, "rank, name, description", "$1, $2, $3", args[0]["rank"].get<int>(), args[0]["name"].get<std::string>(), args[0]["description"].get<std::string>());
    }
