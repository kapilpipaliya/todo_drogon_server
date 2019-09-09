#ifndef SLIDESHOW_H
#define SLIDESHOW_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Slideshow : public BaseServiceAbs {
 public:
  Slideshow(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // SLIDESHOW_H
