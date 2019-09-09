#ifndef M_DB_H
#define M_DB_H

// The libpq-fe.h file contains definitions of enumerations, structures,
// constants, and functions of the C programming interface.
#include <libpq-fe.h>
#include <string>

enum LogMessageType { kLogMsg_User, kLogMsg_App, kLogMsg_ErrorLog };

class M_DB {
 public:
  explicit M_DB();
  ~M_DB();

  bool init();
  void close();

  bool isConnOk();
  static int libVersion();
  int serverVersion();
  PGconn *conn = nullptr;
  std::string lastErrorMessage;
  PGresult *res = nullptr;

  // Command Execution Functions
  bool executeSQL(std::string &statement, bool logsql = true);
  bool executeSQLParams(std::string &statement, int nParams,
                        const char *const *paramValues, bool logsql = true);
  // There is also simple example to insert binary params
  // https://github.com/anmcn/ocpgdb/blob/master/misc/protocmp.c#L87
  //
  bool prepare(std::string &stmtName, std::string &statement, int nParams);
  bool execPrepared(std::string &stmName, int nParams,
                    const char *const *paramValues);
  int nParams();  // Returns the number of parameters of a prepared statement.
  Oid paramType(
      int paramNumber);  // Returns the data type of the indicated statement
                         // parameter. Parameter numbers start at 0.
  bool errorCheck(std::string &stmName);
  // Retrieving Query Result Information
  int rows();
  int columns();
  char *columnName(int columnNumber);        // Column numbers start at 0
  int columnNumber(const char *columnName);  // -1 is returned if the given name
                                             // does not match any column.
  Oid columnTable(int columnNumber);  // Returns the OID of the table from which
                                      // the given column was fetched.
  int tableColumn(
      int columnNumber);  // Returns the column number (within its table) of the
                          // column making up the specified query result
                          // column.Query-result column numbers start at 0, but
                          // table columns have nonzero numbers. Zero is
                          // returned if the column number is out of range,
  int formatCode(
      int columnNumber);  // Returns the format code indicating the format of
                          // the given column. Column numbers start at 0. Format
                          // code zero indicates textual data representation,
                          // while format code one indicates binary
                          // representation.
  Oid columnType(
      int columnNumber);  // Returns the data type associated with the given
                          // column number. The integer returned is the internal
                          // OID number of the type. Column numbers start at 0.
                          // You can query the system table pg_type to obtain
                          // the names and properties of the various data types.
                          // The OIDs of the built-in data types are defined in
                          // the file src/include/catalog/pg_type_d.h in the
                          // source tree.
  char *columnDataType(int columnNumber);
  int colModifier(
      int columnNumber);  // Returns the type modifier of the column associated
                          // with the given column number. Column num- bers
                          // start at 0. The interpretation of modifier values
                          // is type-specific; they typically indicate precision
                          // or size limits. The value -1 is used to indicate
                          // “no information available”. Most data types do not
                          // use modifiers, in which case the value is always
                          // -1.
  int colSize(
      int columnNumber);  // Returns the size in bytes of the column associated
                          // with the given column number. Column num- bers
                          // start at 0. PQfsize returns the space allocated for
                          // this column in a database row, in other words the
                          // size of the server's internal representation of the
                          // data type. (Accordingly, it is not really very
                          // useful to clients.) A negative value indicates the
                          // data type is variable-length.
  char *getValue(
      int rowNumber,
      int columnNumber);  // Returns a single field value of one row of a
                          // PGresult. Row and column numbers start at 0.
  int getIsNull(int rowNumber,
                int columnNumber);  // Tests a field for a null value. Row and
                                    // column numbers start at 0.
  int getLength(
      int rowNumber,
      int columnNumber);  // Returns the actual length of a field value in
                          // bytes. Row and column numbers start at 0.
  void printResult();
  void clearResult();

  /// log an SQL statement [thread-safe]
  // void logSQL(std::string statement, LogMessageType msgtype);

  // This is possible but require Antlr to gnerate sql, so do it manually now..
  // std::string addRecord(const sqlb::ObjectIdentifier& tablename);
  // bool deleteRecords(const sqlb::ObjectIdentifier& table, const
  // std::stringList& rowids, const sqlb::StringVector& pseudo_pk = {}); bool
  // updateRecord(const sqlb::ObjectIdentifier& table, const std::string&
  // column, const std::string& rowid, const QByteArray& value, bool itsBlob,
  // const sqlb::StringVector& pseudo_pk = {}); bool renameTable(const
  // std::string& schema, const std::string& from_table, const std::string&
  // to_table); bool addColumn(const sqlb::ObjectIdentifier& tablename, const
  // sqlb::Field& field);

  // bool loadExtension(const std::string& filename);
  void loadExtensionsFromSettings();
  long long strtolong(int rowNumber, int columnNumber);
  double strtoduble(int rowNumber, int columnNumber);
  bool strbool(int rowNumber, int columnNumber);
  time_t strtotime(int rowNumber, int columnNumber);
  void strtojson(int rowNumber, int columnNumber);

  // signals:
  //    void sqlExecuted(std::string sql, int msgtype);
};

#endif  // M_DB_H
