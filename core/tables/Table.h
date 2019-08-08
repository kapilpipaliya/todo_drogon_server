#ifndef TABLE_H
#define TABLE_H

#include <memory>
#include <vector>


//#include <QVector>
//#include "RowCache.h"

#include "core/connection/mdb.h"
#include "core/connection/pdb.h"
#include "core/sql/objectidentifier.h"
#include "core/sql/query.h"

#include <json/json.h>
#include <pqxx/pqxx>

class Table
{

public:
    explicit Table();
    virtual ~Table();

    P_DB *conn;

    //in the subclass, you actuallly don't need to mark the overriden methods as slots.

public:
    virtual bool select();
    //QModelIndex bottom; // rowCount is calculated from this
    // int bottom; // rowCount // start from 0

    //uint atEnd : 1;
    //QVector<QHash<int, QVariant> > headers; // used in headerData function
    //QVarLengthArray<int, 56> colOffsets; // used to calculate indexInQuery of columns
    //int nestedResetLevel;

    //QSqlRecord record(int row) const; // this function return edit data record.
    //QSqlRecord record() const;

    /// reset to state after construction
    virtual void reset();


    virtual int rowCount() const;

    virtual int columnCount() const;

//    virtual QVariant data(int row, int column, int role = Qt::DisplayRole) const;
//    virtual QVariant headerData(int column) const;
//    virtual QMap<int, QVariant> headerData();

    virtual void clear();
    virtual std::string &lastError() const;

    virtual int fieldIndex(const std::string &fieldName) const;


    virtual int columnNumber(const char *columnName);
    virtual const char *columnName(int columnNumber) const;
    //virtual char *columnDataType(int columnNumber); // Temporary

    virtual bool isEditableColumn(int column) const;
    bool isEditable() const;
//    virtual bool updateAttribute(const QModelIndex &index, const QVariant &value);
    virtual bool deleteRow(int row); // also update cache. // used in table view
    virtual bool removeRow(const char *id);// used in website
    //virtual bool insertRow(int row) = 0;

    virtual void setColumnVisibility(const int column, const bool show);
    virtual void sort(const std::vector<sqlb::SortedColumn>& columns);

    /// clears the cache, resets row-count to unknown (but keeps table
    /// & query info), increase life_counter
    //    void clearCache();

    virtual std::string getHeaderName(const int column) const;
//    QVariant getResult(int row, int column) const;
    Json::Value getJsonHeaderData();
    Json::Value getJsonData();
    size_t filterCount() const;
    sqlb::ObjectIdentifier currentTableName() const
    {
        return m_query.table();
    }

    /// reading something in background right now? (either counting
    /// rows or actually loading data, doesn't matter)
    bool readingData() const;
    // The pseudo-primary key is exclusively for editing views
    void setPseudoPk(std::vector<std::string> pseudoPk);
    bool hasPseudoPk() const;

//    bool isBinary(const QModelIndex& index) const;
    //std::vector<std::string> pseudoPk() const { return m_query.rowIdColumns(); }
    //sqlb::ForeignKeyClause getForeignKeyClause(int column) const;
    //void addCondFormat(int column, const CondFormat& condFormat);
    //void setCondFormats(int column, const std::vector<CondFormat>& condFormats);


    /// trigger asynchronous loading of (at least) the specified row
    /// into cache.
    void triggerCacheLoad (int single_row) const;

    /// trigger asynchronous loading of (at least) the specified rows
    /// into cache. \param row_end is exclusive.
    void triggerCacheLoad (int row_begin, int row_end) const;

    /// wait until not reading any data (that does not mean data is
    /// complete, just that the background reader is idle)
    void waitUntilIdle () const;

    /// load all rows into cache, return when done. Returns true if all data was loaded, false if the loading was cancelled.
    bool completeCache() const;

    /// returns true if all rows are currently available in cache
    /// [NOTE: potentially unsafe in case we have a limited-size
    /// cache, where entries can vanish again -- however we can't do
    /// this for the current implementation of the PlotDock]
    bool isCacheComplete () const;


    /// counts numbers of clearCache() since instantiation; using this
    /// to avoid processing of queued signals originating in an era
    /// before the most recent reset().
    int m_lifeCounter;

    /// note: the row count can be determined by the row-count query
    /// (which yields the "final" row count"), or, if it is faster, by
    /// the first chunk reading actual data (in which case the row
    /// count will be set to that chunk's size and later updated to
    /// the full row count, when the row-count query returns)
    unsigned int m_currentRowCount;


    // Helper function for removing all comments from a SQL query
    static void removeCommentsFromQuery(std::string& query);

    // Add quotes to an identifier
    //std::string escapeIdentifier2(const std::string& id);

    Json::Value getAllData(Json::Value &in);
public:
    pqxx::result result;

    sqlb::ObjectIdentifier m_table;
    sqlb::Query m_query;
    std::string m_sQuery;
    bool saveCache = false;

    std::string insertError;



public:
    void updateFilterBase(Json::Value filters);
    void updateSortBase(Json::Value filters);
    void updatePaginationBase(Json::Value filters);
    void updateFilter(int column, const std::string& whereClause);

private:
    friend class RowLoader;
    class RowLoader * worker;


    /// clears the cache, resets row-count to unknown (but keeps table
    /// & query info), increase life_counter
    void clearCache();

    //void handleFinishedFetch(int life_id, unsigned int fetched_row_begin, unsigned int fetched_row_end);
    //void handleRowCountComplete(int life_id, int num_rows);

    /// \param pDb connection to query; if null, obtains it from 'm_db'.

    // Return matching conditional format color or invalid color, otherwise.
    // Only Qt::ForegroundRole and Qt::BackgroundRole are expected in role (Qt::ItemDataRole)
    //QColor getMatchingCondFormatColor(int column, const std::string& value, int role) const;


//    bool nosync_isBinary(const QModelIndex& index) const;
    //    QMap<int, std::vector<CondFormat>> m_mCondFormats;
    std::vector<int> m_vDataTypes;


    std::string m_encoding;

    /**
     * These are used for multi-threaded population of the table
     */
//    mutable QMutex m_mutexDataCache;

};

#endif // TABLE_H
