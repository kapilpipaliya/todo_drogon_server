#ifndef QUERY_H
#define QUERY_H

#include "objectidentifier.h"

#include <string>
#include <unordered_map>
#include <vector>
#include "core/connection/pdb.h"
/*
 * This file's classes should not talk to database directly
 * */
namespace sqlb
{

enum SortDirection {
    Ascending,
    Descending
};

struct SortedColumn {
    SortedColumn(size_t column_, SortDirection direction_)
        :
        column(column_),
        direction(direction_)
    {}

    bool operator==(const SortedColumn& rhs) const
    {
        return column == rhs.column && direction == rhs.direction;
    }

    size_t column;
    SortDirection direction;
};
struct GroupByColumn {
    GroupByColumn(const std::string &prefix_, const std::string & column_)
        : prefix(prefix_),
          column(column_)
    {}

    bool operator==(const GroupByColumn& rhs) const
    {
        return column == rhs.column && prefix == rhs.prefix;
    }

    std::string prefix;
    std::string column;
};

struct SelectedColumn {
    std::string original_column;
    std::string selector;
    std::string calculated;
    std::string prefix;
    PG_TYPES column_type;
    bool isVisible = true;
    int offset = 0;
    int tooltipOffset = 0;
    bool isEditable = true;
};
struct Join {
    Join(const std::string& join_type, const sqlb::ObjectIdentifier& table, const std::string& condition)
        :
        m_table(table),
        join_type(join_type),
        condition(condition)
    {}
    Join(const std::string& join_type, const std::string& lateral, const std::string& condition)
        :
          lateral(lateral),
          join_type(join_type),
          condition(condition)
    {}

    sqlb::ObjectIdentifier m_table;
    std::string lateral;
    std::string join_type;
    std::string condition;
};
struct SubQuery {
    std::string alias;
    std::vector<SelectedColumn> columns;
};
struct Pagination {
    int limit = 0;
    int offset = 0;
};

class Query
{
public:
    Query() {}
    explicit Query(const sqlb::ObjectIdentifier& table) :
        m_table(table)
    {}

    void clear();
    std::string buildQuery(bool withRowid) const;
    std::string buildCountQuery() const;

    //void setColumNames(const std::vector<std::string>& column_names) { m_column_names = column_names; }
    //std::vector<std::string> columnNames() const { return m_column_names; }

    void setTable(const sqlb::ObjectIdentifier& table)
    {
        m_table = table;
    }
    sqlb::ObjectIdentifier table() const
    {
        return m_table;
    }

    //void setRowIdColumns(const std::vector<std::string>& rowids) { m_rowid_columns = rowids; }
    //std::vector<std::string> rowIdColumns() const { return m_rowid_columns; }
    //void setRowIdColumn(const std::string& rowid) { m_rowid_columns = {rowid}; }
    //bool hasCustomRowIdColumn() const { return m_rowid_columns.size() != 1 || (m_rowid_columns.at(0) != "rowid" && m_rowid_columns.at(0) != "_rowid_"); }

    const std::vector<SelectedColumn>& selectedColumns() const
    {
        return m_selected_columns;
    }
    std::vector<SelectedColumn>& selectedColumns()
    {
        return m_selected_columns;
    }

    std::vector<Join>& joins()
    {
        return m_joins;
    }

    const std::unordered_map<size_t, std::string>& where() const
    {
        return m_where;
    }
    std::unordered_map<size_t, std::string>& where()
    {
        return m_where;
    }

    const std::vector<SortedColumn>& orderBy() const
    {
        return m_sort;
    }
    std::vector<SortedColumn>& orderBy()
    {
        return m_sort;
    }
    void setOrderBy(const std::vector<SortedColumn>& columns)
    {
        m_sort = columns;
    }
    Pagination& pagination()
    {
        return m_pagination;
    }
    void setPagination(const Pagination &p)
    {
        m_pagination = p;
    }
    const std::vector<GroupByColumn>& groupBy() const
    {
        return m_group;
    }
    std::vector<GroupByColumn>& groupBy()
    {
        return m_group;
    }
    const SubQuery& subquery() const
    {
        return m_subquery;
    }
    SubQuery& subquery()
    {
        return m_subquery;
    }
private:
    //std::vector<std::string> m_column_names;
    sqlb::ObjectIdentifier m_table;
    //std::vector<std::string> m_rowid_columns;
    std::vector<SelectedColumn> m_selected_columns;
    std::unordered_map<size_t, std::string> m_where;
    std::vector<SortedColumn> m_sort;
    std::vector<GroupByColumn> m_group;
    std::vector<Join> m_joins;
    Pagination m_pagination;
    SubQuery m_subquery;

    std::vector<SelectedColumn>::iterator findSelectedColumnByName(const std::string& name);
    std::vector<SelectedColumn>::const_iterator findSelectedColumnByName(const std::string& name) const;
    std::string buildWherePart() const;
};

}

#endif
