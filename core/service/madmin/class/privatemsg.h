#ifndef PRIVATEMSG_H
#define PRIVATEMSG_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class PrivateMsg : public BaseServiceAbs
{
public:
    PrivateMsg(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // PRIVATEMSG_H
