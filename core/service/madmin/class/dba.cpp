#include "dba.h"
#include "spdlogfix.h"
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
       SPDLOG_TRACE(e.what());
        throw("Invalid Sql At Dba");
    }
}

unsigned long Dba::num_rows(Result &resource)
{
    //if (resource) {
        //auto result = resource.size();
        //if (result) {
            //return result;
        //}
    //}
    return resource.size();

    //return 0;
}
