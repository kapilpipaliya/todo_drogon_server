#ifndef BROWSE_H
#define BROWSE_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Browse : public BaseServiceAbs
{
public:
    Browse(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // BROWSE_H
