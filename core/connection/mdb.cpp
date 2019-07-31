#include "mdb.h"
#include <cstdlib>
#include <stdexcept>

void do_exit(PGconn *conn)
{

    PQfinish(conn);
    exit(1);
}
void do_exit(PGconn *conn, PGresult *res)
{

    fprintf(stderr, "%s\n", PQerrorMessage(conn));
    fflush(stdout);

    PQclear(res);
    PQfinish(conn);

    exit(1);
}

M_DB::M_DB()
{
    init();
}

M_DB::~M_DB()
{
    close();
}


bool M_DB::init()
{
    if(!conn || PQstatus(conn) == CONNECTION_BAD) {
        conn = PQconnectdb("user=postgres dbname=susant");

        printf("connected to the database\n");
        fflush(stdout);
        if (PQstatus(conn) == CONNECTION_BAD) {

            fprintf(stderr, "Connection to database failed: %s\n",
                    PQerrorMessage(conn));
            do_exit(conn);
        }

        int ver = PQserverVersion(conn);

        printf("Server version: %d\n", ver);
        fflush(stdout);

        return true;
    }
}

void M_DB::close()
{
    if(res) PQclear(res);

    PQfinish(conn);
    printf("closed connection\n");
    fflush(stdout);
}

bool M_DB::isConnOk()
{
    if(!conn || PQstatus(conn) == CONNECTION_BAD) {
        lastErrorMessage = "No database file opened";
        return false;
    }
    return true;
}

int M_DB::libVersion()
{
    return PQlibVersion();
    // printf("Server version: %d\n", ver);
}

int M_DB::serverVersion()
{
    return PQserverVersion(conn);
}

bool M_DB::executeSQL( std::string &statement, bool logsql)
{
    // waitForDbRelease();
    if(!isConnOk()) return false;
    //statement = statement.trimmed();
    // if (logsql) logSQL(statement, kLogMsg_App);
    res = PQexec(conn, statement.data());
    return errorCheck(statement);
}

bool M_DB::executeSQLParams(std::string &statement, int nParams, const char * const *paramValues, bool logsql)
{
    if(!isConnOk()) return false;
    //statement = statement.trimmed();
    // if (logsql) logSQL(statement, kLogMsg_App);
    res = PQexecParams(conn, statement.c_str(), nParams, nullptr, paramValues, nullptr, nullptr, 0);

    return errorCheck(statement);
}

bool M_DB::prepare(std::string &stmtName, std::string &statement, int nParams)
{
    if(!isConnOk()) return false;
    //statement = statement.trimmed();
    // if (logsql) logSQL(statement, kLogMsg_App);
    res = PQprepare(conn, stmtName.c_str(), statement.data(), nParams, nullptr);

    return errorCheck(statement);
}

bool M_DB::execPrepared(std::string &stmName, int nParams, const char * const *paramValues)
{
    if(!isConnOk()) return false;
    // if (logsql) logSQL(statement, kLogMsg_App);
    res = PQexecPrepared(conn, stmName.c_str(), nParams, paramValues, nullptr, nullptr, 0); // only check is it PGRES_COMMAND_OK
    return errorCheck(stmName);
}

int M_DB::nParams()
{
    return PQnparams(res);
}

Oid M_DB::paramType(int paramNumber)
{
    return PQparamtype(res, paramNumber);
}

bool M_DB::errorCheck(std::string &stmName)
{
    if (PQresultStatus(res) == PGRES_TUPLES_OK || PQresultStatus(res) == PGRES_SINGLE_TUPLE || PQresultStatus(res) == PGRES_COMMAND_OK) {
        lastErrorMessage = PQerrorMessage(conn) + std::string("(") + stmName + std::string(")");
        printf("%s%s%s%s\n", "executePreparedSQL: ", stmName.c_str(), "->", PQerrorMessage(conn));
        fflush(stdout);
        return true;
    } else {
        lastErrorMessage = std::string("No data retrieved\n") + PQresStatus(PQresultStatus(res)) + PQresultErrorMessage(res) + PQerrorMessage(conn);
        printf("%s%s%s%s\n", "executePreparedSQL: ", stmName.c_str(), "->", lastErrorMessage.c_str());
        fflush(stdout);
        return false;
    }
}
int M_DB::rows()
{
    return PQntuples(res);
}

int M_DB::columns()
{
    return  PQnfields(res);
}

char *M_DB::columnName(int columnNumber)
{
    return PQfname(res, columnNumber);
}

int M_DB::columnNumber(const char *columnName)
{
    return PQfnumber(res, columnName);
}

Oid M_DB::columnTable(int columnNumber)
{
    return PQftable(res, columnNumber);
}

int M_DB::tableColumn(int columnNumber)
{
    return PQftablecol(res, columnNumber);
}

int M_DB::formatCode(int columnNumber)
{
    return PQfformat(res, columnNumber);
}

Oid M_DB::columnType(int columnNumber)
{
    return PQftype(res, columnNumber);
}

char *M_DB::columnDataType(int columnNumber)
{
    std::string statement = "select typname from pg_type where oid = $1";
    int nParams = 1;
    const char *paramValues[1];

    // how to convert int to char* : https://stackoverflow.com/questions/10847237/how-to-convert-from-int-to-char
    std::string s = std::to_string(columnType(columnNumber));
    char const *pchar = s.c_str();

    paramValues[0] = pchar;
    PGresult *res = PQexecParams(conn, statement.c_str(), nParams, nullptr, paramValues, nullptr, nullptr, 0);
    // Not Checking for error now..
    if (PQresultStatus(res) == PGRES_TUPLES_OK || PQresultStatus(res) == PGRES_SINGLE_TUPLE )
        return PQgetvalue(res, 0, 0);
    else
        return nullptr;
}

int M_DB::colModifier(int columnNumber)
{
    return PQfmod(res, columnNumber);
}

int M_DB::colSize(int columnNumber)
{
    return PQfsize(res, columnNumber);
}
char *M_DB::getValue(int rowNumber, int columnNumber)
{
    return PQgetvalue(res, rowNumber, columnNumber);
    // For data in binary format, read function documentation
    // An empty string is returned if the field value is null. See PQgetisnull to distinguish null values from empty-string values.
}

int M_DB::getIsNull(int rowNumber, int columnNumber)
{
    return PQgetisnull(res, rowNumber, columnNumber);
}

int M_DB::getLength(int rowNumber, int columnNumber)
{
    return PQgetlength(res, rowNumber, columnNumber);
}

void M_DB::printResult()
{
// PQprint()
}

void M_DB::clearResult()
{
    PQclear(res);

}
/*
void M_DB::logSQL(QString statement, LogMessageType msgtype)
{
    // Remove any leading and trailing spaces, tabs, or line breaks first
    statement = statement.trimmed();

    // Replace binary log messages by a placeholder text instead of printing gibberish
    for(int i=0; i<statement.size(); i++) {
        QChar ch = statement[i];
        if(ch < 32 && ch != '\n' && ch != '\r' && ch != '\t') {
            statement.truncate(i>0?i-1:0);
            statement.append(tr("... <string can not be logged, contains binary data> ..."));

            // early exit if we detect a binary character,
            // to prevent checking all characters in a potential big string
            break;
        }
    }

    //emit sqlExecuted(statement, msgtype);
}
*/
/*
bool M_DB::loadExtension(const QString &filename)
{

}
*/
void M_DB::loadExtensionsFromSettings()
{
    if(!isConnOk()) return;
    /*
    sqlite3_enable_load_extension(_db, Settings::getValue("extensions", "enable_load_extension").toBool());

    QStringList list = Settings::getValue("extensions", "list").toStringList();
    for(const QString& ext : list)
    {
        if(loadExtension(ext) == false)
            QMessageBox::warning(nullptr, QApplication::applicationName(), tr("Error loading extension: %1").arg(lastError()));
    }
    */
}

long long M_DB::strtolong(int rowNumber, int columnNumber)
{
    auto r = getValue(rowNumber, columnNumber);
    return strtoll(r, nullptr, 10);
}

double M_DB::strtoduble(int rowNumber, int columnNumber)
{
    auto value = getValue(rowNumber, columnNumber);
    return strtod( value, nullptr );
}

bool M_DB::strbool(int rowNumber, int columnNumber)
{
    auto value = getValue(rowNumber, columnNumber);
    // https://github.com/taocpp/taopq/blob/master/src/lib/pq/result_traits.cpp#L13
    if( value[ 0 ] != '\0' && value[ 1 ] == '\0' ) {
        if( value[ 0 ] == 't' ) {
            return true;
        }
        if( value[ 0 ] == 'f' ) {
            return false;
        }
    }
    throw std::runtime_error( "invalid value in tao::pq::result_traits<bool> for input: " + std::string( value ) );
}

time_t M_DB::strtotime(int rowNumber, int columnNumber)
{
    // excact answer:
    // c++ convert postgres timestamp without time zone to time_t
    // https://stackoverflow.com/questions/22208971/c-convert-postgres-timestamp-without-time-zone-to-time-t

    //Conversion of times in C++
    //https://stackoverflow.com/questions/46230320/conversion-of-times-in-c

    //http://www.cplusplus.com/reference/ctime/
    auto value = getValue(rowNumber, columnNumber);
    //asctime()
}

void M_DB::strtojson(int rowNumber, int columnNumber)
{
    // if a query result column is of json or jsonb type, then PQgetvalue will return a pointer to the json text as a string
}
//so to encrypt a password use  crypt('mypassword', gen_salt('bf',10))  or whatever value other than 10 isn't too slow for you (default is 6)
//then use  WHERE storedpass = crypt(supplied_pass, storedpass)   to check whether an input value is correct


// making sure you don't overrun the value buffer
// you know, basic defensive C coding
