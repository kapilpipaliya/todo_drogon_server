#ifndef PREFERENCE_H
#define PREFERENCE_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Preference : public BaseServiceAbs
{
public:
    Preference(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // PREFERENCE_H
