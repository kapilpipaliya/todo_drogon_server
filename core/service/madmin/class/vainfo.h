#ifndef VAINFO_H
#define VAINFO_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class VaInfo : public BaseServiceAbs
{
public:
    VaInfo(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // VAINFO_H
