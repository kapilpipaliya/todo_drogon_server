#include "Table.h"
#include <iostream>
#include "spdlogfix.h"

#include "../strfns.h"
#include "condformat.h"
#include <drogon/WebSocketController.h>

Table::Table()
{
    reset();
}

Table::~Table()
{

}
bool Table::select()
{
    auto q = m_query.buildQuery(true);
    SPDLOG_TRACE(q);
    // crash !! auto clientPtr = drogon::app().getFastDbClient("sce");
    auto clientPtr = drogon::app().getDbClient("sce");
    *clientPtr << q << Mode::Blocking >> [this](const Result &r) {
        result = r;
    } >> [q](const DrogonDbException &e) {
        SPDLOG_TRACE("query: {}", q);
       SPDLOG_TRACE(e.base().what());
        //testOutput(false, "DbClient streaming-type interface(0)");
        throw;
    };
    return true;
}

int Table::rowCount() const
{
    return result.size();
}

int Table::columnCount() const
{
    return result.columns();
}

// Convert a number to string using the Unicode superscript characters
template<class T>
static std::string toSuperScript(T number)
{
    std::string superScript = std::to_string(number);
    ReplaceAll2(superScript, "0", "⁰");
    ReplaceAll2(superScript, "1", "¹");
    ReplaceAll2(superScript, "2", "²");
    ReplaceAll2(superScript, "3", "³");
    ReplaceAll2(superScript, "4", "⁴");
    ReplaceAll2(superScript, "5", "⁵");
    ReplaceAll2(superScript, "6", "⁶");
    ReplaceAll2(superScript, "7", "⁷");
    ReplaceAll2(superScript, "8", "⁸");
    ReplaceAll2(superScript, "9", "⁹");
    return superScript;
}

void Table::clear()
{

}
std::string &Table::lastError() const
{
    std::string s = "";
    return s;
}
const char *Table::columnName(int columnNumber) const
{
    if(result.empty()) {
        return m_query.selectedColumns().at(columnNumber).original_column.c_str();
    } else {
        return result.columnName(columnNumber);
    }
}
bool Table::isEditableColumn(int column) const
{
    if (column < 0 || column >= columnCount()) {
        return false;
    }
    return  m_query.selectedColumns().at(column).isEditable;

}
std::string Table::getHeaderName(const int column) const
{
    return m_query.selectedColumns().at(column).original_column;
}
void Table::reset()
{
    m_query.clear(); // this will clear sort table everything on table...
    m_sQuery.clear();
    //m_headers.clear();
    //m_vDataTypes.clear();
    //m_mCondFormats.clear();
}

json Table::getJsonHeaderData()
{
    json ret(json::array());

    json jsonHeaderRow(json::array());
    json jsonFormHeaderRow(json::array());
    json jsonFormColumnTypesRow(json::array());
    json jsonFormVisibleColumnsRow(json::array());
    json jsonFormOffsetColumnsRow(json::array());
    json jsonFormTooltipOffsetColumnsRow(json::array());

    for (unsigned long c=0; c < m_query.selectedColumns().size(); c++) {
        jsonHeaderRow[c] = getHeaderName(c);
        auto column = m_query.selectedColumns().at(c);
        jsonFormColumnTypesRow[c] = column.column_type;
        jsonFormVisibleColumnsRow[c] = column.isVisible;
        jsonFormOffsetColumnsRow[c] = column.offset;
        jsonFormTooltipOffsetColumnsRow[c] = column.tooltipOffset;

        if(column.prefix.empty()) {
            jsonFormHeaderRow[c] = column.original_column; // can change case
        } else {
            if(column.prefix == m_table.as()) {
                jsonFormHeaderRow[c] = column.selector;
            } else {
                jsonFormHeaderRow[c] = column.prefix + "_" + column.selector;
            }
        }
    }
    ret.push_back(jsonHeaderRow);
    ret.push_back(jsonFormHeaderRow);
    ret.push_back(jsonFormColumnTypesRow);
    ret.push_back(jsonFormVisibleColumnsRow);
    ret.push_back(jsonFormOffsetColumnsRow);
    ret.push_back(jsonFormTooltipOffsetColumnsRow);
    return ret;
}

json Table::getJsonData()
{
    json jresult = json::array();

    for(unsigned long row=0; row<rowCount(); row++) {
        json jsonRow;
        for(unsigned long column=0; column<columnCount(); column++) {
            if(result[row][column].isNull()) {
                json j(nullptr);
                jsonRow[column] = j;
                continue;
            }
            auto ctype = m_query.selectedColumns().at(column).column_type;
            switch (ctype) {
            case PG_TYPES::INT4:
            case PG_TYPES::INT8:
                //jsonRow[column] = (long)strtolong(row, column);
                jsonRow[column] = result[row][column].as<long>();
                break;
            case PG_TYPES::BOOL:{
                //jsonRow[column] = strbool(row, column);
                auto r5 = result[row][column].as<std::string>();
                //jsonRow[column] = result[row][column].as<bool>();
                jsonRow[column] = result[row][column].as<std::string>() == "t" ? true : false;
                break;
            }
//          case PG_TYPES::
            case PG_TYPES::DOUBLE:
                //jsonRow[column] = strbool(row, column);
                jsonRow[column] = result[row][column].as<double>();
                break;
            /*case PG_TYPES::ARRAYINT: {
                auto jsonArray = json(json::array());
                auto ar = result[row][column].as_array();
                auto jnc = ar.get_next();
                while (jnc.first != array_parser::done) {
                    if(jnc.first == array_parser::string_value) {
                        int myint = stoi(jnc.second);
                        jsonArray.push_back(myint);
                    }
                    jnc = ar.get_next();

                }
                jsonRow[column] = jsonArray;
            }
            break;
            case PG_TYPES::ARRAYTEXT: {
                auto jsonArray = json(json::array());
                auto ar = result[row][column].as_array();
                auto jnc = ar.get_next();
                while (jnc.first != array_parser::done) {
                    if(jnc.first == array_parser::string_value)
                        jsonArray.push_back(jnc.second);
                    jnc = ar.get_next();

                }
                jsonRow[column] = jsonArray;
            }
            break;*/
            case PG_TYPES::PSJSON: {
                auto valin = json::parse(result[row][column].c_str());
                jsonRow[column] = valin;
            }
            break;
            case PG_TYPES::TEXT:
            default:
                //jsonRow[column] = getValue(row, column);
                jsonRow[column] = result[row][column].c_str();
            }
        }
        jresult.push_back(jsonRow);
    }
    return jresult;
}
void Table::sort(const std::vector<sqlb::SortedColumn> &columns)
{
    // Don't do anything when the sort order hasn't changed
    if(m_query.orderBy() == columns)
        return;

    // Save sort order
    m_query.orderBy() = columns;

    // Set the new query (but only if a table has already been set

    if(!m_query.table().isEmpty())
        //buildQuery();
        select();

}

json Table::getAllData(json &args)
{
//    printJson(args);
    updateFilterBase(args[0]);
    updateSortBase(args[1]);
    updatePaginationBase(args[2]);
    select();
    return getJsonData();
}

void Table::updateFilterBase(json filters)
{
    if (filters.is_null() || filters.size() == 0 || !filters.is_array()) {
        return;
    }
    for (unsigned int i=0; i < filters.size(); i++) {

//         == json::value_t::string
        std::string v{""};
        if (filters[i].is_null()) {
            v  = "";
        } else if(filters[i].type() == json::value_t::number_integer ||  filters[i].type() == json::value_t::number_unsigned) {
            v = std::to_string(filters[i].get<long>());
        } else if (filters[i].type() == json::value_t::number_float) {
            v = std::to_string(filters[i].get<float>());
        } else if(filters[i].type() == json::value_t::boolean) {
            v = filters[i].get<bool>() ? "true" : "false";
        } else if (filters[i].type() == json::value_t::string) {
            v = filters[i].get<std::string>();
        } else {
            v = "";
        }
        std::string whereClause = CondFormat::filterToSqlCondition(v, m_query.selectedColumns().at(i).column_type, "");
        // If the value was set to an empty string remove any filter for this column. Otherwise insert a new filter rule or replace the old one if there is already one
        if(whereClause.empty())
            m_query.where().erase(static_cast<size_t>(i));
        else
            m_query.where()[static_cast<size_t>(i)] = whereClause;
    }
}
void Table::updateSortBase(json filters)
{
    if (filters.is_null() || filters.size() == 0 || !filters.is_array()) {
        return;
    }
    for (unsigned int i=0; i < filters.size(); i++) {
        if(filters[i].is_null()) {
            continue;
        } else if(filters[i].get<int>() == 0) {
            m_query.orderBy().emplace_back(i, sqlb::Ascending);
        } else {
            m_query.orderBy().emplace_back(i, sqlb::Descending);
        }
    }
}
void Table::updatePaginationBase(json filters)
{
    if (filters.is_null() || filters.size() == 0 || !filters.is_array()) {
        return;
    }
    if(!filters[0].is_null()) {
        m_query.pagination().limit = filters[0].get<int>();
    }
    if(!filters[1].is_null()) {
        m_query.pagination().offset = filters[1].get<int>();
    }
    if(!filters[2].is_null()) {
        m_query.pagination().current_page = filters[2].get<int>();
    }
}
size_t Table::filterCount() const
{
    return m_query.where().size();
}
void Table::updateFilter(int column, const std::string &whereClause)
{
    // If the value was set to an empty string remove any filter for this column. Otherwise insert a new filter rule or replace the old one if there is already one
    if(whereClause.empty())
        m_query.where().erase(static_cast<size_t>(column));
    else
        m_query.where()[static_cast<size_t>(column)] = whereClause;
    // Build the new query
    //buildQuery();

    select();
}
