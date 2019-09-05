#ifndef USERFLAG_H
#define USERFLAG_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class UserFlag : public BaseServiceAbs
{
public:
    UserFlag(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // USERFLAG_H
