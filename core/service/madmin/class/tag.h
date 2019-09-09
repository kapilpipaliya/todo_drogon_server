#ifndef TAG_H
#define TAG_H

#include "../../../../wscontroller/context/madmincontext.h"

#include "core/sql/query.h"
using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Tag {
 public:
  Tag(MAdminContextPtr);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  void setupTable();

 private:
  MAdminContextPtr context;
  sqlb::Query query;
};
}  // namespace madmin
#endif  // TAG_H
