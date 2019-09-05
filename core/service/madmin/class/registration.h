#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class Registration : public BaseServiceAbs
{
public:
    Registration(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // REGISTRATION_H
