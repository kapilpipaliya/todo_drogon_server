#ifndef Generator_H
#define Generator_H

#include "core/sql/query.h"
#include "json.hpp"

namespace generator {
namespace service {
class Generator {
 public:
  Generator();
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);

 private:
  void setupTable();

  sql::Query query;
};
}  // namespace service
}  // namespace jadmin
#endif  // Generator_H
