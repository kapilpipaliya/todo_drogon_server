#ifndef PLAYLISTBASE_H
#define PLAYLISTBASE_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class PlayListBase : public BaseServiceAbs {
 public:
  PlayListBase(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // PLAYLISTBASE_H
