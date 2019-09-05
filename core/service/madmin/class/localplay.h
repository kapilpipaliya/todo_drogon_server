#ifndef LOCALPLAY_H
#define LOCALPLAY_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class LocalPlay : public BaseServiceAbs
{
public:
    LocalPlay(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // LOCALPLAY_H
