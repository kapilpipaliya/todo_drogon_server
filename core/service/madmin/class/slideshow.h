#ifndef SLIDESHOW_H
#define SLIDESHOW_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class Slideshow : public BaseServiceAbs
{
public:
    Slideshow(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // SLIDESHOW_H
