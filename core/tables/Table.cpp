#include "Table.h"
#include "functions.h"
#include <pqxx/pqxx>
#include <iostream>
#include "condformat.h"

Table::Table(QObject *parent) : QObject(parent)
{
//    dbConnSelect = new M_DB;
    reset();

}

Table::~Table()
{
//    delete dbConnSelect;
}
bool Table::select()
{
    //    ReplaceAll2(query, "%1", m_table.schema());
    //    ReplaceAll2(query, "%2", m_table.name());

    auto q = m_query.buildQuery(true);
    // to print out query:
    //fprintf(stdout, "%s\n", q.c_str());
    //fflush(stdout);

    /* temporary
    if(!executeSQL(q)) {
        //d->clearCache();
        return false;
    }
    */

    pqxx::work txn{DD};
    try {
        result = txn.exec(q);
        txn.commit();
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        throw;

    }

    // set cache:
    /*
    if(saveCache) {
        cache.clear();
        for(int i=0; i<rows(); i++) {
            for(int c=0; c<columns(); c++) {
                cache[i][c] = getResult(i, c);
            }
        }
    }
    */
    return true;
}

int Table::rowCount() const
{
//    return rows();
    return result.size();
}

int Table::columnCount() const
{
//    return columns();
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
// used in model
QVariant Table::headerData(int column) const // column == section
{

    std::string sortIndicator;
    for(size_t i = 0; i < m_query.orderBy().size(); i++) {
        const sqlb::SortedColumn sortedColumn = m_query.orderBy()[i];
        // Append sort indicator with direction and ordinal number in superscript style
        if (sortedColumn.column == static_cast<size_t>(column)) {
            sortIndicator = sortedColumn.direction == sqlb::Ascending ? " ▾" : " ▴";
            sortIndicator.append(toSuperScript(i+1));
            break;
        }
    }
    auto s = getHeaderName(column) + sortIndicator;
    return QString::fromStdString(s);

}
// used in website
QMap<int, QVariant> Table::headerData()
{
    QMap<int, QVariant> headers;
    for (int c=0; c < columnCount(); c++) {
        headers[c] = QString::fromStdString(getHeaderName(c));
    }
    return headers;
}

void Table::clear()
{

}

std::string &Table::lastError() const
{
//    return lastErrorMessage;
    std::string s = "";
    return s;
}

int Table::fieldIndex(const QString &fieldName) const
{
    //    return rec.indexOf(fieldName);
}


int Table::columnNumber(const char *columnName)
{
//    return columnNumber(columnName);
    return 0;
}

const char *Table::columnName(int columnNumber) const
{
//    return columnName(columnNumber);
    if(result.empty()) {
        return m_query.selectedColumns().at(columnNumber).original_column.c_str();
    } else {
        return result.column_name(columnNumber);
    }
}
/*
char *Table::columnDataType(int columnNumber)
{
    return columnDataType(columnNumber);
}*/

bool Table::isEditableColumn(int column) const
{
    if (column < 0 || column >= columnCount()) {
        return false;
    }

    return  m_query.selectedColumns().at(column).isEditable;

}
bool Table::isEditable() const
{
    //    return !m_query.table().isEmpty() &&
    //        m_db.isOpen() &&
    //        ((m_db.getObjectByName(m_query.table()) && m_db.getObjectByName(m_query.table())->type() == sqlb::Object::Types::Table) || m_query.hasCustomRowIdColumn());
    return true;
}
void Table::setColumnVisibility(const int column, const bool show)
{
    // pretty complex at /mnt/sce/old_pc/git/kmymoney-master/kmymoney/models/accountsmodel.cpp:701
}

std::string Table::getHeaderName(const int column) const
{

    return m_query.selectedColumns().at(column).original_column;
}

void Table::reset()
{
    emit beginResetModel();
    //clearCache();

    // Todo manage this in seperate accessorry class.
    m_query.clear(); // this will clear sort table everything on table...
    m_sQuery.clear();
    //m_headers.clear();
    //m_vDataTypes.clear();
    //m_mCondFormats.clear();

    emit endResetModel();
}

QVariant Table::data(int row, int column, int role) const
{
    // return cached data, if manually managing cache and cache = true
    switch (role) {
    case Qt::EditRole: {
        return getResult(row, column);
    }
    case Qt::DisplayRole: {
        QString tableColumnName = columnName(column);
        // 1.we can disply different text for null field, blob field, also display ... if text > some limit in settings. see sqlitebrowser code...
        // 2.we can also find ForeignKeyConstraintType constraint on field, if it found, its foreignkey.
        // /home/kapili3/k/sqlitebrowser-master/src/sqliteTable.cpp:412
        return getResult(row, column + m_query.selectedColumns().at(column).offset);
    }
    case Qt::ToolTipRole: {
        if(m_query.selectedColumns().at(column).tooltipOffset) {
            return getResult(row, column + m_query.selectedColumns().at(column).tooltipOffset);
        } else {
            return  QVariant();
        }
    }
    default:
        return QVariant();
    }
    // if its null we can make font italic. and change foreground and background color.
    // if it is fk, we can disply tooltip that press Shift and clcick to jump there. see sqlite Table.cpp
}
QVariant Table::getResult(int row, int column) const
{
    auto ctype = m_query.selectedColumns().at(column).column_type;
    switch (ctype) {
    case PG_TYPES::INT4:
    case PG_TYPES::INT8:
//        return strtolong(row, column);
        return result[row][column].as<int>(0);
    case PG_TYPES::BOOL:
        //return strbool(row, column);
        return result[row][column].as<bool>();
    case PG_TYPES::TEXT:
    default:
        //return getValue(row, column);
        return result[row][column].c_str();
    }
}

Json::Value Table::getJsonHeaderData()
{
    Json::Value jsonHeaderRow(Json::arrayValue);
    for (int c=0; c < m_query.selectedColumns().size(); c++) {
        jsonHeaderRow[c] = getHeaderName(c);
    }
    return jsonHeaderRow;
}

Json::Value Table::getJsonData()
{
    Json::Value jresult;

    for(int row=0; row<rowCount(); row++) {
        Json::Value jsonRow;
        for(int column=0; column<columnCount(); column++) {
            auto ctype = m_query.selectedColumns().at(column).column_type;
            switch (ctype) {
            case PG_TYPES::INT4:
            case PG_TYPES::INT8:
                //jsonRow[column] = (long)strtolong(row, column);
                jsonRow[column] = result[row][column].as<long>(0);
                break;
            case PG_TYPES::BOOL:
                //jsonRow[column] = strbool(row, column);
                jsonRow[column] = result[row][column].as<bool>();
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
bool Table::updateAttribute(const QModelIndex &index, const QVariant &value)
{
    if (!index.isValid() || index.column() >= columnCount() || index.row() >= rowCount())
        return false;
    M_DB updateConnection;

    auto cName = columnName(index.column());
    std::string strSql = "update %1.%2 set %3 = $1 where id = $2";
    ReplaceAll2(strSql, "%1", m_table.schema());
    ReplaceAll2(strSql, "%2", m_table.name());
    ReplaceAll2(strSql, "%3", cName);

//    auto id = getValue(index.row(), 0);
    auto id = result[index.row()][0].c_str();
    const char *values[2];
    if (!value.toString().isEmpty()) {
        values[0] = value.toByteArray();
    } else
        values[0] = nullptr; //  «A null pointer in this array means the corresponding parameter is null»
    values[1] = id;
    /* temporary
    if(!updateConnection.executeSQLParams(strSql, 2, values)) {
        return false;
    } else {
        if(saveCache)
            cache[index.row()][index.column()].setValue(value);
        return true;
    }*/
    return  false;
}
void Table::sort(const std::vector<sqlb::SortedColumn> &columns)
{
    // Don't do anything when the sort order hasn't changed
    if(m_query.orderBy() == columns)
        return;

    // Save sort order
    m_query.orderBy() = columns;

    // Set the new query (but only if a table has already been set
    emit beginResetModel();
    if(!m_query.table().isEmpty())
        //buildQuery();
        select();
    emit endResetModel();
}
// used in table view, cache must be enable to work this:
bool Table::deleteRow(int row)
{
//    auto id = getValue(row, 0);
    auto id = result[row][0].c_str();

    if(!removeRow(id)) {
        return false;
    } else {
        /*
        //clear cache:
        QMap<int, QMap<int, QVariant> >::Iterator it = cache.find(row);
        if (it == cache.end())
            return false;
        it = cache.erase(it);
        while (it != cache.end()) {
            int oldKey = it.key();
            const QMap<int, QVariant> oldValue = it.value();
            cache.erase(it);
            it = cache.insert(oldKey - 1, oldValue); // Remove and insert rows
            ++it;
        }
        */
        return true;
    }
}
// used in website
bool Table::removeRow(const char *id)
{
    P_DB *deleteConnection = new P_DB;

    std::string strSql = "DELETE FROM %1.%2 WHERE id = $1;";
    ReplaceAll2(strSql, "%1", m_table.schema());
    ReplaceAll2(strSql, "%2", m_table.name());
    const char *values[1];
    //char buffer[5];
    //sprintf(buffer, "%d", row); // or you can use binary format for that parameter, and use htonl() to convert it to network byte order
    values[0] = id;
    /* temporary
    if(!deleteConnection->executeSQLParams(strSql, 1, values)) {
        emit statusMessage(deleteConnection->lastErrorMessage);
        return false;
    } else
        return true;
    */
    return false;

}
void Table::removeCommentsFromQuery(QString &query)
{
    int oldSize = query.size();

    // first remove block comments
    {
        QRegExp rxSQL("^((?:(?:[^'/]|/(?![*]))*|'[^']*')*)(/[*](?:[^*]|[*](?!/))*[*]/)(.*)$");	// set up regex to find block comment
        QString result;

        while(query.size() != 0) {
            int pos = rxSQL.indexIn(query);
            if(pos > -1) {
                result += rxSQL.cap(1) + " ";
                query = rxSQL.cap(3);
            } else {
                result += query;
                query = "";
            }
        }
        query = result;
    }

    // deal with end-of-line comments
    {
        /* The regular expression for removing end of line comments works like this:
         * ^((?:(?:[^'-]|-(?!-))*|(?:'[^']*'))*)(--.*)$
         * ^                                          $ # anchor beginning and end of string so we use it all
         *  (                                  )(    )  # two separate capture groups for code and comment
         *                                       --.*   # comment starts with -- and consumes everything afterwards
         *   (?:                 |           )*         # code is none or many strings alternating with non-strings
         *                        (?:'[^']*')           # a string is a quote, followed by none or more non-quotes, followed by a quote
         *      (?:[^'-]|-(?!-))*                       # non-string is a sequence of characters which aren't quotes or hyphens,
         */

        QRegExp rxSQL("^((?:(?:[^'-]|-(?!-))*|(?:'[^']*'))*)(--[^\\r\\n]*)([\\r\\n]*)(.*)$");	// set up regex to find end-of-line comment
        QString result;

        while(query.size() != 0) {
            int pos = rxSQL.indexIn(query);
            if(pos > -1) {
                result += rxSQL.cap(1) + rxSQL.cap(3);
                query = rxSQL.cap(4);
            } else {
                result += query;
                query = "";
            }
        }

        query = result.trimmed();
    }

    if (oldSize != query.size()) {
        // Remove multiple line breaks that might have been created by deleting comments till the end of the line but not including the line break
        query.replace(QRegExp("\\n+"), "\n");

        // Also remove any remaining whitespace at the end of each line
        query.replace(QRegExp("[ \t]+\n"), "\n");
    }
}

void Table::updateFilterBase(Json::Value filters)
{
    if (filters.isNull() || filters.size() == 0 || filters.type() != Json::ValueType::arrayValue) {
        return;
    }
    for (unsigned int i=0; i < filters.size(); i++) {
        QString whereClause = CondFormat::filterToSqlCondition(QString::fromStdString(filters.get(i, "").asString()), m_encoding);
        // If the value was set to an empty string remove any filter for this column. Otherwise insert a new filter rule or replace the old one if there is already one
        if(whereClause.isEmpty())
            m_query.where().erase(static_cast<size_t>(i));
        else
            m_query.where()[static_cast<size_t>(i)] = whereClause.toStdString();
    }
}

size_t Table::filterCount() const
{
    return m_query.where().size();
}

bool Table::readingData() const
{
    //    return worker->readingData();
    return false;
}

void Table::updateFilter(int column, const QString &whereClause)
{
    // If the value was set to an empty string remove any filter for this column. Otherwise insert a new filter rule or replace the old one if there is already one
    if(whereClause.isEmpty())
        m_query.where().erase(static_cast<size_t>(column));
    else
        m_query.where()[static_cast<size_t>(column)] = whereClause.toStdString();
    // Build the new query
    //buildQuery();
    emit beginResetModel();
    select();
    emit endResetModel();
}

void Table::clearCache()
{
    //m_lifeCounter++;

    //    if(m_db.isOpen()) {
    //        worker->cancel();
    //        worker->waitUntilIdle();
    //    }
    /*
    if(m_currentRowCount > 0)
    {
        beginRemoveRows(QModelIndex(), 0, static_cast<int>(m_currentRowCount - 1));
        endRemoveRows();
    }

    //    m_cache.clear();
    m_currentRowCount = 0;
    m_rowCountAvailable = RowCount::Unknown;
    */
}
/*
sqlb::ForeignKeyClause TableModel::getForeignKeyClause(int column) const
{
    static const sqlb::ForeignKeyClause empty_foreign_key_clause;

    // No foreign keys when not browsing a table. This usually happens when executing custom SQL statements
    // and browsing the result set instead of browsing an entire table.
    if(m_query.table().isEmpty())
        return empty_foreign_key_clause;

    // Retrieve database object and check if it is a table. If it isn't stop here and don't return a foreign
    // key. This happens for views which don't have foreign keys (though we might want to think about how we
    // can check for foreign keys in the underlying tables for some purposes like tool tips).
//    sqlb::ObjectPtr obj = m_db.getObjectByName(m_query.table());
//    if(obj->type() != sqlb::Object::Table)
//        return empty_foreign_key_clause;

    // Convert object to a table and check if the column number is in the valid range
    sqlb::TablePtr tbl = std::dynamic_pointer_cast<sqlb::Table>(obj);
    if(tbl && tbl->name().size() && (column >= 0 && column < static_cast<int>(tbl->fields.size())))
    {
        // Note that the rowid column has number -1 here, it can safely be excluded since there will never be a
        // foreign key on that column.

        sqlb::ConstraintPtr ptr = tbl->constraint({tbl->fields.at(static_cast<size_t>(column)).name()}, sqlb::Constraint::ForeignKeyConstraintType);
        if(ptr)
            return *(std::dynamic_pointer_cast<sqlb::ForeignKeyClause>(ptr));
    }

    return empty_foreign_key_clause;
}
*/
QByteArray Table::encode(const QByteArray& str) const
{
    //    return encodeString(str, m_encoding);
}

QByteArray Table::decode(const QByteArray& str) const
{
    //    return decodeString(str, m_encoding);
}
void Table::setPseudoPk(std::vector<std::string> pseudoPk)
{
    if(pseudoPk.empty())
        pseudoPk.emplace_back("_rowid_");

    // Do nothing if the value didn't change
    //    if(m_query.rowIdColumns() == pseudoPk)
    //        return;

    //    m_query.setRowIdColumns(pseudoPk);
    //    if(m_headers.size())
    //        m_headers[0] = sqlb::joinStringVector(pseudoPk, ",");

    //buildQuery();
}

bool Table::hasPseudoPk() const
{
    //    return m_query.hasCustomRowIdColumn();
}

bool Table::isBinary(const QModelIndex& index) const
{
    //QMutexLocker lock(&m_mutexDataCache);
    //return nosync_isBinary(index);
    return false;
}

bool Table::nosync_isBinary(const QModelIndex& index) const
{
    const size_t row = static_cast<size_t>(index.row());
    //    if(!m_cache.count(row))
    //        return false;

    //    const auto & cached_row = m_cache.at(row);

    //    return !isTextOnly(cached_row.at(static_cast<size_t>(index.column())), m_encoding, true);
}

void Table::triggerCacheLoad (int row) const
{
    /*
    int halfChunk = static_cast<int>( m_chunkSize / 2);
    size_t row_begin = static_cast<std::size_t>(std::max(0, row - halfChunk));
    size_t row_end = static_cast<std::size_t>(row + halfChunk);

    if(rowCountAvailable() == RowCount::Complete)
    {
        row_end = std::min(row_end, static_cast<std::size_t>(rowCount()));
    } else {
        // will be truncated by reader
    }

    // avoid re-fetching data
    QMutexLocker lk(&m_mutexDataCache);
    //    m_cache.smallestNonAvailableRange(row_begin, row_end);

    //    if(row_end != row_begin)
    //        worker->triggerFetch(m_lifeCounter, row_begin, row_end);
    */
}

void Table::triggerCacheLoad (int row_begin, int row_end) const
{
    if(row_end == row_begin)
        return;

    triggerCacheLoad((row_begin + row_end) / 2);
}

bool Table::completeCache () const
{
    /*
    // Show progress dialog because fetching all data might take some time but only show
    // cancel button if we allow cancellation here. This isn't
    //    QProgressDialog progress(tr("Fetching data..."),
    //                             tr("Cancel"), 0, rowCount());
    //    progress.setWindowModality(Qt::ApplicationModal);
    //    progress.show();

    waitUntilIdle();

    // This loop fetches all data by loading it block by block into the cache
    for(int i = 0; i < (rowCount() + static_cast<int>( m_chunkSize / 2)); i += static_cast<int>(m_chunkSize))
    {
        //        progress.setValue(i);
        //        qApp->processEvents();
        //        if(progress.wasCanceled())
        //            return false;

        triggerCacheLoad(i);
        //        worker->waitUntilIdle();
    }
    */
    return true;
}

bool Table::isCacheComplete () const
{
    if(readingData())
        return false;
    //QMutexLocker lock(&m_mutexDataCache);
    //    return m_cache.numSet() == m_currentRowCount;
    return true;
}

void Table::waitUntilIdle () const
{
    //worker->waitUntilIdle();
}

