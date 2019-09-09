#ifndef BOOKMARK_H
#define BOOKMARK_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Bookmark : public BaseServiceAbs {
 public:
  Bookmark(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // BOOKMARK_H
