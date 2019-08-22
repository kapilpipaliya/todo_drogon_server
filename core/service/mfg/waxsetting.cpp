#include "waxsetting.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

WaxSetting::WaxSetting(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{
    t.m_table = sqlb::ObjectIdentifier("mfg", "wax_setting", "m");

}

void WaxSetting::setupTable()
{
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "m", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Rank", "rank", "", "m", PG_TYPES::INT4, true}),
            sqlb::SelectedColumn({"No", "no", "", "m", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Sequence", "sequence_id", "", "m", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Date", "date", "", "m", PG_TYPES::TIMESTAMP, true}),
            sqlb::SelectedColumn({"Department", "department_id", "", "m", PG_TYPES::INT8, false, 1, 1}),
            sqlb::SelectedColumn({"Name", "name", "", "dep", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Employee", "employee_id", "", "m", PG_TYPES::INT8, false, 1, 1}),
            sqlb::SelectedColumn({"e_name", "slug", "", "e", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Description", "description", "", "m", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Status", "status_id", "", "m", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Branch", "branch_id", "", "m", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "m", PG_TYPES::INT8, true, 1}),
            sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "m", PG_TYPES::INT8, true, 1}),
            sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "m", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "m", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto dep = sqlb::ObjectIdentifier("mfg", "department", "dep");
    auto e = sqlb::ObjectIdentifier("entity", "entity", "e");
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", dep, "dep.id = m.department_id"),
            sqlb::Join("left", e, "e.id = m.employee_id"),
            sqlb::Join("left", u1, "m.create_user_id = u1.id"),
            sqlb::Join("left", u2, "m.update_user_id = u2.id"),
            };
}

json WaxSetting::ins(json event, json args)
{
    return insBase(event, args, "date, department_id, employee_id, description, status_id", "$1, $2, $3, $4, $5",
                   args[0]["date"].get<std::string>(),
                                  args[0]["department_id"].get<int>(), args[0]["employee_id"].get<int>(), args[0]["description"].get<std::string>(),
                                  args[0]["status_id"].get<std::string>()
            );
}

json WaxSetting::upd(json event, json args)
{
    return updBase(event, args, "date, department_id, employee_id, description, status_id", "$1, $2, $3, $4, $5",
                   args[0]["date"].get<std::string>(),
                                  args[0]["department_id"].get<int>(), args[0]["employee_id"].get<int>(), args[0]["description"].get<std::string>(),
                                  args[0]["status_id"].get<std::string>()
            );
}
