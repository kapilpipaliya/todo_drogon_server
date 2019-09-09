#ifndef SLIDESHOW_H
#define SLIDESHOW_H

#include "../../../../wscontroller/context/madmincontext.h"

#include "core/sql/query.h"

namespace madmin {
class Slideshow {
 public:
  Slideshow(std::shared_ptr<MAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  void setupTable();

 private:
  std::shared_ptr<MAdminContext> context;
  sqlb::Query query;
};
}  // namespace madmin
#endif  // SLIDESHOW_H
