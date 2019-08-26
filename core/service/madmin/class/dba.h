#ifndef DBA_H
#define DBA_H
#include <string>
#include <drogon/HttpAppFramework.h>

#include "../baseservice.h"
namespace madmin {
class Dba : public BaseService
{
public:
    Dba();
    void setupTable() override;
    static drogon::orm::Result read(std::string sql);
};
}
#endif // DBA_H
