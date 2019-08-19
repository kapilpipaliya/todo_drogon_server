#ifndef PDB_H
#define PDB_H
#pragma once
#include <pqxx/pqxx>
using namespace pqxx;
#include <string>
inline connection DD("user=postgres dbname=susant");
/*
enum PG_TYPES {
    BOOL = 16,
    //    ByTea = 17,
    //    Char = 18,
    INT8 = 20,
    INT4 = 23,
    TEXT = 25,
  //  JSON = 114,
    XML = 142,
    DOUBLE = 701,
    TIMESTAMP = 1114,
    ENUM = 64000,
    //ARRAYINT = 9997, // fix
    //ARRAYTEXT = 9998, // fix
    PSJSON = 9999
};

*/
class P_DB
{

public:
    explicit P_DB();
    ~P_DB();

    connection *C;
public:
    bool init();
};

#endif // PDB_H
