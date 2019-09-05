#ifndef LOCALPLAYBASE_H
#define LOCALPLAYBASE_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class LocalPlayBase : public BaseServiceAbs
{
public:
    LocalPlayBase(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // LOCALPLAYBASE_H
