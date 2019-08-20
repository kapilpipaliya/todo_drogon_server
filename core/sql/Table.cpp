#include "../strfns.h"
#include "Table.h"

#include <iostream>
#include "condformat.h"
#include <drogon/WebSocketController.h>
#include "../../EchoWebSocket.h"

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
    // to print out query:
//    fprintf(stdout, "%s\n", q.c_str());
//    fflush(stdout);
    // crash !! auto clientPtr = drogon::app().getFastDbClient("sce");

    *clientPtr << q << Mode::Blocking >> [this](const Result &r) {
        result = r;
    } >> [q](const DrogonDbException &e) {
        std::cout << "query: " << q << std::endl;
        std::cerr << e.base().what() << std::endl;
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

Json::Value Table::getJsonHeaderData()
{
    Json::Value ret(Json::arrayValue);

    Json::Value jsonHeaderRow(Json::arrayValue);
    Json::Value jsonFormHeaderRow(Json::arrayValue);
    Json::Value jsonFormColumnTypesRow(Json::arrayValue);
    Json::Value jsonFormVisibleColumnsRow(Json::arrayValue);
    Json::Value jsonFormOffsetColumnsRow(Json::arrayValue);
    Json::Value jsonFormTooltipOffsetColumnsRow(Json::arrayValue);

    for (int c=0; c < m_query.selectedColumns().size(); c++) {
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
    ret.append(jsonHeaderRow);
    ret.append(jsonFormHeaderRow);
    ret.append(jsonFormColumnTypesRow);
    ret.append(jsonFormVisibleColumnsRow);
    ret.append(jsonFormOffsetColumnsRow);
    ret.append(jsonFormTooltipOffsetColumnsRow);
    return ret;
}

Json::Value Table::getJsonData()
{
    Json::Value jresult(Json::arrayValue);

    for(int row=0; row<rowCount(); row++) {
        Json::Value jsonRow;
        for(int column=0; column<columnCount(); column++) {
            if(result[row][column].isNull()) {
                jsonRow[column] = Json::Value(Json::nullValue);
                continue;
            }
            auto ctype = m_query.selectedColumns().at(column).column_type;
            switch (ctype) {
            case PG_TYPES::INT4:
            case PG_TYPES::INT8:
                //jsonRow[column] = (long)strtolong(row, column);
                jsonRow[column] = result[row][column].as<long>();
                break;
            case PG_TYPES::BOOL:
                //jsonRow[column] = strbool(row, column);
                jsonRow[column] = result[row][column].as<bool>();
                break;
//          case PG_TYPES::
            case PG_TYPES::DOUBLE:
                //jsonRow[column] = strbool(row, column);
                jsonRow[column] = result[row][column].as<double>();
                break;
            /*case PG_TYPES::ARRAYINT: {
                auto jsonArray = Json::Value(Json::arrayValue);
                auto ar = result[row][column].as_array();
                auto jnc = ar.get_next();
                while (jnc.first != array_parser::done) {
                    if(jnc.first == array_parser::string_value) {
                        int myint = stoi(jnc.second);
                        jsonArray.append(myint);
                    }
                    jnc = ar.get_next();

                }
                jsonRow[column] = jsonArray;
            }
            break;
            case PG_TYPES::ARRAYTEXT: {
                auto jsonArray = Json::Value(Json::arrayValue);
                auto ar = result[row][column].as_array();
                auto jnc = ar.get_next();
                while (jnc.first != array_parser::done) {
                    if(jnc.first == array_parser::string_value)
                        jsonArray.append(jnc.second);
                    jnc = ar.get_next();

                }
                jsonRow[column] = jsonArray;
            }
            break;*/
            case PG_TYPES::PSJSON: {
                Json::Reader reader;
                Json::Value valin;
                reader.parse(result[row][column].c_str(),  valin);
                jsonRow[column] = valin;
            }
            break;
            case PG_TYPES::TEXT:
            default:
                //jsonRow[column] = getValue(row, column);
                jsonRow[column] = result[row][column].c_str();
            }
        }
        jresult.append(jsonRow);
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

Json::Value Table::getAllData(Json::Value &args)
{
//    printJson(args);
    updateFilterBase(args[0]);
    updateSortBase(args[1]);
    updatePaginationBase(args[2]);
    select();
    return getJsonData();
}

void Table::updateFilterBase(Json::Value filters)
{
    if (filters.isNull() || filters.size() == 0 || filters.type() != Json::ValueType::arrayValue) {
        return;
    }
    for (unsigned int i=0; i < filters.size(); i++) {
        std::string whereClause = CondFormat::filterToSqlCondition(filters.get(i, "").asString(), m_query.selectedColumns().at(i).column_type, "");
        // If the value was set to an empty string remove any filter for this column. Otherwise insert a new filter rule or replace the old one if there is already one
        if(whereClause.empty())
            m_query.where().erase(static_cast<size_t>(i));
        else
            m_query.where()[static_cast<size_t>(i)] = whereClause;
    }
}
void Table::updateSortBase(Json::Value filters)
{
    if (filters.isNull() || filters.size() == 0 || filters.type() != Json::ValueType::arrayValue) {
        return;
    }
    for (unsigned int i=0; i < filters.size(); i++) {
        if(filters[i].isNull()) {
            continue;
        } else if(filters[i].asInt() == 0) {
            m_query.orderBy().emplace_back(i, sqlb::Ascending);
        } else {
            m_query.orderBy().emplace_back(i, sqlb::Descending);
        }
    }
}
void Table::updatePaginationBase(Json::Value filters)
{
    if (filters.isNull() || filters.size() == 0 || filters.type() != Json::ValueType::arrayValue) {
        return;
    }
    if(!filters[0].isNull()) {
        m_query.pagination().limit = filters[0].asInt();
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
