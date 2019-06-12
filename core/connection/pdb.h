#ifndef PDB_H
#define PDB_H
#pragma once
#include <pqxx/pqxx>
using namespace pqxx;
#include <string>
extern connection DD;
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
