#ifndef DBA_H
#define DBA_H
#include <string>
#include <drogon/HttpAppFramework.h>

class Dba
{
public:
    Dba();
    static drogon::orm::Result read(std::string sql);
};

#endif // DBA_H
