#ifndef CSSIZE_H
#define CSSIZE_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "core/sql/query.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class CSSize {
 public:
  CSSize(JAdminContextPtr);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);

 private:
  void setupTable();
  nlohmann::json ins(nlohmann::json event, nlohmann::json args);
  nlohmann::json upd(nlohmann::json event, nlohmann::json args);
  nlohmann::json del(nlohmann::json event, nlohmann::json args);
  JAdminContextPtr context;
  sqlb::Query query;
};
}  // namespace jadmin
#endif  // CSSIZE_H
