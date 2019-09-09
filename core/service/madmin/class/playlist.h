#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class PlayList : public BaseServiceAbs {
 public:
  PlayList(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // PLAYLIST_H
