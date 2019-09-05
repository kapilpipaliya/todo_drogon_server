#ifndef USERFLAG_H
#define USERFLAG_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class UserFlag : public BaseServiceAbs
{
public:
    UserFlag(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // USERFLAG_H
