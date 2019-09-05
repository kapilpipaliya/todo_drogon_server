#ifndef SHOUTBOX_H
#define SHOUTBOX_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class ShoutBox : public BaseServiceAbs
{
public:
    ShoutBox(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // SHOUTBOX_H
