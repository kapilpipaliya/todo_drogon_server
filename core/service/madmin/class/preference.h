#ifndef PREFERENCE_H
#define PREFERENCE_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class Preference : public BaseServiceAbs
{
public:
    Preference(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // PREFERENCE_H
