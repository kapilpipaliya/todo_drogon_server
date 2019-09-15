#include "dba.h"
#include "spdlogfix.h"
namespace sql {
Dba::Dba() = default;

drogon::orm::Result Dba::read(const std::string& sql) {
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    auto res = clientPtr->execSqlSync(sql);
    return res;
  } catch (const std::exception& e) {
    SPDLOG_TRACE(e.what());
    throw std::runtime_error("Invalid Sql At Dba");
  }
}

nlohmann::json Dba::readJson(const std::string& sql) {
  // Fix this. dont know how to do it?
  nlohmann::json j;
  return j;
}

unsigned long Dba::num_rows(drogon::orm::Result& resource) {
  // if (resource) {
  // auto result = resource.size();
  // if (result) {
  // return result;
  //}
  //}
  return resource.size();

  // return 0;
}
}  // namespace sql
