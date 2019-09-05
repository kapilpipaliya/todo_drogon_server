#pragma once

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Access : public BaseServiceAbs
{
public:
    Access(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
