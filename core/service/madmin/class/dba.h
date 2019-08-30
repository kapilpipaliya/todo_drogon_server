#ifndef DBA_H
#define DBA_H
#include <string>
#include <drogon/HttpAppFramework.h>

#include "../baseservice.h"
namespace madmin {
/**
 * Dba Class
 *
 * This is the database abstraction class
 * It duplicates the functionality of mysql_???
 * with a few exceptions, the row and assoc will always
 * return an array, simplifying checking on the far end
 * it will also auto-connect as needed, and has a default
 * database simplifying queries in most cases.
 *
 */
class Dba : public BaseService
{
public:
    Dba(const MAdminContextPtr &);
    void setupTable() override;


/* Make sure they aren't directly accessing it */

    //public static std::string stats = array('query' => 0);

    //private static std::string _sql;
    //private static std::string _error;

    /**
     * query
     */
    //static void query(std::string sql, std::string params = array());

    //private static function _query(std::string sql, std::string params);
    /**
     * read
     */
    static drogon::orm::Result read(std::string sql);

    template<class... Args>
    static drogon::orm::Result read(std::string sql, Args... args){
        try {
            auto clientPtr = drogon::app().getDbClient("sce");
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sql, args...);
            return r;
        } catch (const std::exception &e) {
           SPDLOG_TRACE(e.what());
            throw("Invalid Sql At Dba write");
        }
    }

    static json readJson(std::string sql);
    /**
     * write
     */
    template<class... Args>
    static drogon::orm::Result write(std::string sql, Args... args){
        try {
            auto clientPtr = drogon::app().getDbClient("sce");
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sql, args...);
            return r;
        } catch (const std::exception &e) {
           SPDLOG_TRACE(e.what());
            throw("Invalid Sql At Dba write");
        }
    }
    /**
     * escape
     *
     * This runs a escape on a variable so that it can be safely inserted
     * into the sql
     */
    //static void escape(std::string var);
    /**
     * fetch_assoc
     *
     * This emulates the mysql_fetch_assoc.
     * We force it to always return an array, albeit an empty one
     * The optional finish parameter affects whether we automatically clean
     * up the result set after the last row is read.
     */
    //static void fetch_assoc(std::string resource, std::string finish = true);
    /**
     * fetch_row
     *
     * This emulates the mysql_fetch_row
     * we force it to always return an array, albeit an empty one
     * The optional finish parameter affects whether we automatically clean
     * up the result set after the last row is read.
     */
    //static void fetch_row(std::string resource, std::string finish = true);
    //static void fetch_object(std::string resource, std::string class = 'stdClass', std::string finish = true);
    /**
     * num_rows
     *
     * This emulates the mysql_num_rows function which is really
     * just a count of rows returned by our select statement, this
     * doesn't work for updates or inserts.
     */
    static unsigned long num_rows(drogon::orm::Result &resource);
    /**
     * finish
     *
     * This closes a result handle and clears the memory associated with it
     */
    //static void finish(std::string resource);
    /**
     * affected_rows
     *
     * This emulates the mysql_affected_rows function
     */
    //static void affected_rows(std::string resource);
    /**
     * _connect
     *
     * This connects to the database, used by the DBH function
     */
    //private static function _connect();
    //private static function _setup_dbh(std::string dbh, std::string database);
    /**
     * check_database
     *
     * Make sure that we can connect to the database
     */
    //static void check_database();
    /**
     * check_database_inserted
     *
     * Checks to make sure that you have inserted the database
     * and that the user you are using has access to it.
     */
    //static void check_database_inserted();
    /**
     * show_profile
     *
     * This function is used for debug, helps with profiling
     */
    //static void show_profile();
    /**
     * dbh
     *
     * This is called by the class to return the database handle
     * for the specified database, if none is found it connects
     */
    //static void dbh(std::string database='');
    /**
     * disconnect
     *
     * This nukes the dbh connection, this isn't used very often...
     */
    //static void disconnect(std::string database = '');
    /**
     * insert_id
     */
    //static void insert_id();
    /**
     * error
     * this returns the error of the db
     */
    //static void error();
    /**
     * translate_to_mysqlcharset
     *
     * This translates the specified charset to a mysql charset.
     */
    //static void translate_to_mysqlcharset(std::string charset);
    /**
     * reset_db_charset
     *
     * This cruises through the database and trys to set the charset to the
     * current site charset. This is an admin function that can be run by an
     * administrator only. This can mess up data if you switch between charsets
     * that are not overlapping.
     */
    //static void reset_db_charset();
    /**
     * optimize_tables
     *
     * This runs an optimize on the tables and updates the stats to improve
     * join speed.
     * This can be slow, but is a good idea to do from time to time. We do
     * it in case the dba isn't doing it... which we're going to assume they
     * aren't.
     */
    //static void optimize_tables();




};
}
#endif // DBA_H
