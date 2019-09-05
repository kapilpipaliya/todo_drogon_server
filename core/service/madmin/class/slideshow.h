#ifndef SLIDESHOW_H
#define SLIDESHOW_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Slideshow : public BaseServiceAbs
{
public:
    Slideshow(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // SLIDESHOW_H
