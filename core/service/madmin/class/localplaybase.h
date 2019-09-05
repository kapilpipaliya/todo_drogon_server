#ifndef LOCALPLAYBASE_H
#define LOCALPLAYBASE_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class LocalPlayBase : public BaseServiceAbs
{
public:
    LocalPlayBase(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // LOCALPLAYBASE_H
