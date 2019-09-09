#ifndef TMPPLAYLIST_H
#define TMPPLAYLIST_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class TmpPlayList : public BaseServiceAbs {
 public:
  TmpPlayList(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // TMPPLAYLIST_H
