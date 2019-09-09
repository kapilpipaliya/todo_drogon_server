#ifndef SONGPREVIEW_H
#define SONGPREVIEW_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class SongPreview : public BaseServiceAbs {
 public:
  SongPreview(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // SONGPREVIEW_H
