#include "dba.h"
#include "spdlog/spdlog.h"
using namespace  madmin;
Dba::Dba(const MAdminContextPtr &context_): BaseService(context_)
{

}

void Dba::setupTable()
{

}

drogon::orm::Result Dba::read(std::string sql)
{
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto res = clientPtr->execSqlSync( sql);
        return res;
    } catch (const std::exception &e) {
        spdlog::error(e.what());
        throw("Invalid Sql At Dba");
    }
}
