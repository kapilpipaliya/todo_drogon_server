#ifndef PDB_H
#define PDB_H
#pragma once
#include <pqxx/pqxx>
using namespace pqxx;
#include <string>
extern connection DD;

enum PG_TYPES {
    BOOL = 16,
    //    ByTea = 17,
    //    Char = 18,
    INT8 = 20,
    INT4 = 23,
    TEXT = 25,
    JSON = 114,
    XML = 142,
    DOUBLE = 701,
    TIMESTAMP = 1114,
    ENUM = 64000,
    //ARRAYINT = 9997, // fix
    //ARRAYTEXT = 9998, // fix
    PSJSON = 9999
};


class P_DB
{

public:
    explicit P_DB();
    ~P_DB();

    connection *C;
public:
    bool init();
    void close();

//    bool isConnOk();
//    static int libVersion();
//    int serverVersion();

    std::string lastErrorMessage;


    //Retrieving Query Result Information
    int rows();
    int columns();
    char *columnName(int columnNumber); // Column numbers start at 0
    int columnNumber(const char *columnName); // -1 is returned if the given name does not match any column.
    char* getValue(int rowNumber, int columnNumber); // Returns a single field value of one row of a PGresult. Row and column numbers start at 0.

};

#endif // PDB_H
