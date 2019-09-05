#ifndef SHOUTBOX_H
#define SHOUTBOX_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class ShoutBox : public BaseServiceAbs
{
public:
    ShoutBox(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // SHOUTBOX_H
