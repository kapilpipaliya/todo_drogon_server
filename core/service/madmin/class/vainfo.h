#ifndef VAINFO_H
#define VAINFO_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class VaInfo : public BaseServiceAbs
{
public:
    VaInfo(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // VAINFO_H
