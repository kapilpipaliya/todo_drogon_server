#ifndef ARTIST_H
#define ARTIST_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Artist : public BaseServiceAbs {
 public:
  Artist(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // ARTIST_H
