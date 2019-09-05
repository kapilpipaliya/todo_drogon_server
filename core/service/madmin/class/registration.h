#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Registration : public BaseServiceAbs
{
public:
    Registration(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // REGISTRATION_H
