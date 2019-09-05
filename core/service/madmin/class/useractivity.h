#ifndef USERACTIVITY_H
#define USERACTIVITY_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class UserActivity : public BaseServiceAbs
{
public:
    UserActivity(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // USERACTIVITY_H
