#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#pragma once

#include <QString>
#include  <cctype>

#include "core/tables/Table.h"
#include "core/sql/objectidentifier.h"
#include "core/sql/query.h"

// trim from start (in place)
static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s)
{
    ltrim(s);
    rtrim(s);
}


// trim from start (copying)
static inline std::string ltrim_copy(std::string s)
{
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s)
{
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s)
{
    trim(s);
    return s;
}

static inline void ReplaceAll2(std::string &str, const std::string& from, const std::string& to)
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
}
namespace
{

QString rtrimChar(const QString& s, QChar c)
{
    QString r = s.trimmed();
    while(r.endsWith(c))
        r.chop(1);
    return r;
}

std::string rtrimChar(const std::string& s, char c)
{
    auto r = trim_copy(s);
    if (r.at(r.size() - 1) == c) {
        r.pop_back();
    }
    return s;
}

} // anon ns

//------------------
namespace
{

void accessorySetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("material", "accessories", "a");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "a", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Material", "material_id", "a", PG_TYPES::INT8, true, 1, 2), sqlb::SelectedColumn("m_slug", "slug", "m", PG_TYPES::TEXT, false, 0, 0, false), sqlb::SelectedColumn("m_name", "name", "m", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Rank", "rank", "a", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Code", "slug", "a", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "a", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    auto m = sqlb::ObjectIdentifier("material", "materials", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        sqlb::Join("left", m, "a.material_id = m.id"),
        sqlb::Join("left", u1, "a.create_user_id = u1.id"),
        sqlb::Join("left", u2, "a.update_user_id = u2.id"),
    };
}

void accountSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("account", "accounts", "a");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "a", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Material", "material_id", "a", PG_TYPES::INT8, true, 1, 2), sqlb::SelectedColumn("m_slug", "slug", "m", PG_TYPES::TEXT, false), sqlb::SelectedColumn("m_name", "name", "m", PG_TYPES::TEXT, false),
        sqlb::SelectedColumn("Rank", "rank", "a", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Code", "slug", "a", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "a", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    auto m = sqlb::ObjectIdentifier("material", "materials", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        sqlb::Join("left", m, "a.material_id = m.id"),
        sqlb::Join("left", u1, "a.create_user_id = u1.id"),
        sqlb::Join("left", u2, "a.update_user_id = u2.id"),
    };
}

void accountHeadingSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("account", "account_headings", "p");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "p", PG_TYPES::INT8, false),

    };

    //auto c = sqlb::ObjectIdentifier("material", "colors", "c");
    //auto pg = sqlb::ObjectIdentifier("part", "part_categories", "pg");
    //auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    //auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        //sqlb::Join("left", c, "p.color_id = c.id"),
        //sqlb::Join("left", pg, "p.part_group_id = pg.id"),
        //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
        //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
    };
}

void colorSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("material", "colors", "c");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "c", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Material", "material_id", "c", PG_TYPES::INT8, true, 1, 2), sqlb::SelectedColumn("m_slug", "slug", "m", PG_TYPES::TEXT, false, 0, 0, false), sqlb::SelectedColumn("m_name", "name", "m", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Rank", "rank", "c", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Code", "slug", "c", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "c", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "c", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "c", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "c", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "c", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    auto m = sqlb::ObjectIdentifier("material", "materials", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        sqlb::Join("left", m, "c.material_id = m.id"),
        sqlb::Join("left", u1, "c.create_user_id = u1.id"),
        sqlb::Join("left", u2, "c.update_user_id = u2.id"),
    };
}

void entitySetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("entity", "entities", "a");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "a", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Material", "material_id", "a", PG_TYPES::INT8, true, 1, 2), sqlb::SelectedColumn("m_slug", "slug", "m", PG_TYPES::TEXT, false, 0, 0, false), sqlb::SelectedColumn("m_name", "name", "m", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Rank", "rank", "a", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Code", "slug", "a", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "a", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    auto m = sqlb::ObjectIdentifier("material", "materials", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        sqlb::Join("left", m, "a.material_id = m.id"),
        sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
        sqlb::Join("left", u2, "a.update_user_id = u2.id"),
    };

}


void gemClaritySetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("material", "gem_clarities", "g");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "g", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Material", "material_id", "g", PG_TYPES::INT8, true, 1, 2), sqlb::SelectedColumn("m_slug", "slug", "m", PG_TYPES::TEXT, false, 0, 0, false), sqlb::SelectedColumn("m_name", "name", "m", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Rank", "rank", "g", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Code", "slug", "g", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "g", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "g", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "g", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "g", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "g", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    auto m = sqlb::ObjectIdentifier("material", "materials", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        sqlb::Join("left", m, "g.material_id = m.id"),
        sqlb::Join("left", u1, "g.create_user_id = u1.id"),
        sqlb::Join("left", u2, "g.update_user_id = u2.id"),
    };
}

void gemShapeSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("material", "gem_shapes", "gs");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "gs", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Material", "material_id", "gs", PG_TYPES::INT8, true, 1, 2), sqlb::SelectedColumn("m_slug", "slug", "m", PG_TYPES::TEXT, false, 0, 0, false), sqlb::SelectedColumn("m_name", "name", "m", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Rank", "rank", "gs", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Code", "slug", "gs", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "gs", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "gs", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "gs", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "gs", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "gs", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    auto m = sqlb::ObjectIdentifier("material", "materials", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        sqlb::Join("left", m, "gs.material_id = m.id"),
        sqlb::Join("left", u1, "gs.create_user_id = u1.id"),
        sqlb::Join("left", u2, "gs.update_user_id = u2.id"),
    };

}


void gemSizeSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("entity", "gem_sizes", "a");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "a", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Material", "material_id", "a", PG_TYPES::INT8, true, 1, 2), sqlb::SelectedColumn("m_slug", "slug", "m", PG_TYPES::TEXT, false, 0, 0, false), sqlb::SelectedColumn("m_name", "name", "m", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Rank", "rank", "a", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Code", "slug", "a", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "a", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    auto m = sqlb::ObjectIdentifier("material", "materials", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        sqlb::Join("left", m, "a.material_id = m.id"),
        sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
        sqlb::Join("left", u2, "a.update_user_id = u2.id"),
    };

}

void gemTypeSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("material", "gem_types", "gt");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "gt", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Rank", "rank", "gt", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Code", "slug", "gt", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "gt", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "gt", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "gt", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "gt", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "gt", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    //auto m = sqlb::ObjectIdentifier("material", "materials", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        //sqlb::Join("left", m, "a.material_id = m.id"),
        sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
        sqlb::Join("left", u2, "gt.update_user_id = u2.id"),
    };

}


void globalSettingSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("setting", "global_settings", "gs");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Setting_key", "setting_key", "gs", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Value", "value", "gs", PG_TYPES::TEXT, true)
    };

    //auto m = sqlb::ObjectIdentifier("material", "materials", "m");
    //auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    //auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        //sqlb::Join("left", m, "a.material_id = m.id"),
        //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
        //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
    };

}

void logSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("setting", "simple_logs", "a");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "a", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Detail", "detail", "a", PG_TYPES::TEXT, true),
        //sqlb::SelectedColumn("Created By", "create_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        //sqlb::SelectedColumn("Updated By", "update_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    //auto m = sqlb::ObjectIdentifier("material", "materials", "m");
    //auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    //auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        //sqlb::Join("left", m, "a.material_id = m.id"),
        //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
        //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
    };
}

void materialSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("material", "materials", "m");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "m", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Material Type", "material_type_id", "m", PG_TYPES::INT8, true, 1, 2), sqlb::SelectedColumn("mt_slug", "slug", "mt", PG_TYPES::TEXT, false, 0, 0, false), sqlb::SelectedColumn("mt_name", "name", "mt", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Rank", "rank", "m", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Code", "slug", "m", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "m", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "m", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "m", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "m", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "m", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    auto mt = sqlb::ObjectIdentifier("material", "material_types", "mt");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        sqlb::Join("left", mt, "m.material_type_id = mt.id"),
        sqlb::Join("left", u1, "m.create_user_id = u1.id"),
        sqlb::Join("left", u2, "m.update_user_id = u2.id"),
    };
}

void materialTypeSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("material", "material_types", "mt");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "mt", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Rank", "rank", "mt", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Code", "slug", "mt", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "mt", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "mt", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "mt", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "mt", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "mt", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    //auto m = sqlb::ObjectIdentifier("material", "materials", "mt");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        //sqlb::Join("left", m, "mt.material_id = m.id"),
        sqlb::Join("left", u1, "mt.create_user_id = u1.id"),
        sqlb::Join("left", u2, "mt.update_user_id = u2.id"),
    };

}

void metalPuritySetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("material", "metal_purities", "mp");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "mp", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Material", "material_id", "mp", PG_TYPES::INT8, true, 1, 2), sqlb::SelectedColumn("m_slug", "slug", "m", PG_TYPES::TEXT, false, 0, 0, false), sqlb::SelectedColumn("m_name", "name", "m", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Rank", "rank", "mp", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Code", "slug", "mp", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "mp", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Purity", "purity", "mp", PG_TYPES::TEXT, true),//FIX
        sqlb::SelectedColumn("Specific_density", "specific_density", "mp", PG_TYPES::TEXT, true),//FIX
        sqlb::SelectedColumn("Currency_id", "currency_id", "mp", PG_TYPES::INT8, true), // Fix this
        sqlb::SelectedColumn("Amount", "amount", "mp", PG_TYPES::TEXT, true),//FIX
        sqlb::SelectedColumn("Description", "description", "mp", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "mp", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "mp", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "mp", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "mp", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    auto m = sqlb::ObjectIdentifier("material", "materials", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        sqlb::Join("left", m, "mp.material_id = m.id"),
        sqlb::Join("left", u1, "mp.create_user_id = u1.id"),
        sqlb::Join("left", u2, "mp.update_user_id = u2.id"),
    };

}

void orderSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("account", "orders", "a");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "a", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Material", "material_id", "a", PG_TYPES::INT8, true, 1, 2), sqlb::SelectedColumn("m_slug", "slug", "m", PG_TYPES::TEXT, false, 0, 0, false), sqlb::SelectedColumn("m_name", "name", "m", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Rank", "rank", "a", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Code", "slug", "a", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "a", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    auto m = sqlb::ObjectIdentifier("material", "materials", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        sqlb::Join("left", m, "a.material_id = m.id"),
        sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
        sqlb::Join("left", u2, "a.update_user_id = u2.id"),
    };

}

void partGroupSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("part", "part_categories", "p");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "p", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Parent", "parent_id", "p", PG_TYPES::INT8, true, 1, 2), sqlb::SelectedColumn("p_slug", "slug", "p2", PG_TYPES::TEXT, false, 0, 0, false), sqlb::SelectedColumn("p_name", "name", "p2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Code", "slug", "p", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "p", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "p", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "p", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "p", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "p", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    auto m = sqlb::ObjectIdentifier("part", "part_categories", "p2");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        sqlb::Join("left", m, "p.parent_id = p2.id"),
        sqlb::Join("left", u1, "u1.id = p.create_user_id"),
        sqlb::Join("left", u2, "u2.id = p.update_user_id"),
    };

}


void partTypeSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("part", "part_types", "pt");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "pt", PG_TYPES::INT8, false),
        //sqlb::SelectedColumn("Rank", "rank", "pt", PG_TYPES::INT4, true),
        //sqlb::SelectedColumn("Code", "slug", "pt", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "pt", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "pt", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "pt", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "pt", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "pt", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    //auto m = sqlb::ObjectIdentifier("material", "materials", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        //sqlb::Join("left", m, "a.material_id = m.id"),
        sqlb::Join("left", u1, "pt.create_user_id = u1.id"),
        sqlb::Join("left", u2, "pt.update_user_id = u2.id"),
    };

}

void productSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("product", "products", "p");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "p", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Directory", "dir_path", "p", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("File Name", "file_name", "p", PG_TYPES::TEXT, true),
        //sqlb::SelectedColumn("Color", "color_id", "p", PG_TYPES::INT8, true, 1, 2),
        //sqlb::SelectedColumn("C_slug", "slug", "c", PG_TYPES::TEXT, false, 0, 0, false),
        //sqlb::SelectedColumn("C_name", "name", "c", PG_TYPES::TEXT, false, 0, 0, false),
        //sqlb::SelectedColumn("Category", "part_group_id", "p", PG_TYPES::INT8, true, 1, 2),
        //sqlb::SelectedColumn("Pg_slug", "slug", "pg", PG_TYPES::TEXT, false, 0, 0, false),
        //sqlb::SelectedColumn("Pg_name", "name", "pg", PG_TYPES::TEXT, false, 0, 0, false),

        sqlb::SelectedColumn("Date", "post_date", "post", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Title", "post_title", "post", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Status", "post_status", "post", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Comment", "comment_status", "post", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "post_name", "post", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Modified", "post_modified", "post", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Parent", "post_parent", "post", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Menu Order", "menu_order", "post", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Post Type", "post_type", "post", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("MIME Type", "post_mime_type", "post", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Comment Count", "comment_count", "post", PG_TYPES::TEXT, true),

        sqlb::SelectedColumn("SKU", "sku", "p", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Virtual", "virtual", "p", PG_TYPES::BOOL, true),
        sqlb::SelectedColumn("Downloadable", "downloadable", "p", PG_TYPES::BOOL, true),
        sqlb::SelectedColumn("Min Price", "min_price", "p", PG_TYPES::INT8, true),
        sqlb::SelectedColumn("Max Price", "max_price", "p", PG_TYPES::INT8, true),
        sqlb::SelectedColumn("On sale", "onsale", "p", PG_TYPES::BOOL, true),
        sqlb::SelectedColumn("Stock Quantity", "stock_quantity", "p", PG_TYPES::INT8, true),
        sqlb::SelectedColumn("Stock Status", "stock_status", "p", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Rating Count", "rating_count", "p", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Average Ratng", "average_ratng", "p", PG_TYPES::INT8, true),
        sqlb::SelectedColumn("Total Sales", "total_sales", "p", PG_TYPES::INT8, true),
        sqlb::SelectedColumn("Total Count", "total_count", "p", PG_TYPES::INT4, true),

        sqlb::SelectedColumn("First Image", "first_image", "p", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Second Image", "second_image", "p", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Third Image", "third_image", "p", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Fourth Image", "fourth_image", "p", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Fifth Image", "fifth_image", "p", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Sixth Image", "sixth_image", "p", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Seventh Image", "seventh_image", "p", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Eighth Image", "eighth_image", "p", PG_TYPES::TEXT, true),



        sqlb::SelectedColumn("Create Time", "inserted_at", "p", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "p", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    //auto c = sqlb::ObjectIdentifier("material", "colors", "c");
    //auto pg = sqlb::ObjectIdentifier("part", "part_categories", "pg");
    auto post = sqlb::ObjectIdentifier("product", "posts", "post");
    //auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    //auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        //sqlb::Join("left", c, "p.color_id = c.id"),
        //sqlb::Join("left", pg, "p.part_group_id = pg.id"),
        sqlb::Join("left", post, "p.post_id = post.id"),
        //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
        //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
    };
}


void rateOnSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("material", "rate_ons", "r");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "r", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Material_type_id", "material_type_id", "r", PG_TYPES::INT8, true, 1, 2), sqlb::SelectedColumn("mt_slug", "slug", "mt", PG_TYPES::TEXT, false, 0, 0, false), sqlb::SelectedColumn("mt_name", "name", "mt", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Rank", "rank", "r", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Code", "slug", "r", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "r", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "r", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "r", PG_TYPES::INT8, true, 1), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "r", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "r", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    auto m = sqlb::ObjectIdentifier("material", "material_types", "mt");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        sqlb::Join("left", m, "r.material_type_id = mt.id"),
        sqlb::Join("left", u1, "r.create_user_id = u1.id"),
        sqlb::Join("left", u2, "r.update_user_id = u2.id"),
    };

}


void saleSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("account", "sales", "a");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "a", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Material", "material_id", "a", PG_TYPES::INT8, true, 1, 2), sqlb::SelectedColumn("m_slug", "slug", "m", PG_TYPES::TEXT, false, 0, 0, false), sqlb::SelectedColumn("m_name", "name", "m", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Rank", "rank", "a", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Code", "slug", "a", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "a", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    auto m = sqlb::ObjectIdentifier("material", "materials", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        sqlb::Join("left", m, "a.material_id = m.id"),
        sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
        sqlb::Join("left", u2, "a.update_user_id = u2.id"),
    };

}

void transactionSetupQuery(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("account", "transactions", "a");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn("Id", "id", "a", PG_TYPES::INT8, false),
        sqlb::SelectedColumn("Material", "material_id", "a", PG_TYPES::INT8, true, 1, 2), sqlb::SelectedColumn("m_slug", "slug", "m", PG_TYPES::TEXT, false, 0, 0, false), sqlb::SelectedColumn("m_name", "name", "m", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Rank", "rank", "a", PG_TYPES::INT4, true),
        sqlb::SelectedColumn("Code", "slug", "a", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Name", "name", "a", PG_TYPES::TEXT, true),
        sqlb::SelectedColumn("Created By", "create_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u1_username", "username", "u1", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Updated By", "update_user_id", "a", PG_TYPES::INT8, true, 1, 0, false), sqlb::SelectedColumn("u2_username", "username", "u2", PG_TYPES::TEXT, false, 0, 0, false),
        sqlb::SelectedColumn("Create Time", "inserted_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
        sqlb::SelectedColumn("Update Time", "updated_at", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false),
    };

    auto m = sqlb::ObjectIdentifier("material", "materials", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "users", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "users", "u2");

    t.m_query.joins() = {
        sqlb::Join("left", m, "a.material_id = m.id"),
        sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
        sqlb::Join("left", u2, "a.update_user_id = u2.id"),
    };
}
}

#endif // FUNCTIONS_H
