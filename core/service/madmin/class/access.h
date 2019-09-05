#pragma once

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class Access : public BaseServiceAbs
{
public:
    Access(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
