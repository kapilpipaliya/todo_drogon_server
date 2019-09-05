#ifndef PRIVATEMSG_H
#define PRIVATEMSG_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class PrivateMsg : public BaseServiceAbs
{
public:
    PrivateMsg(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // PRIVATEMSG_H
