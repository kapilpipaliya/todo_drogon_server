#ifndef USERACTIVITY_H
#define USERACTIVITY_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class UserActivity : public BaseServiceAbs
{
public:
    UserActivity(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // USERACTIVITY_H
