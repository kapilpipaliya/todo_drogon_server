#ifndef LOCALPLAY_H
#define LOCALPLAY_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class LocalPlay : public BaseServiceAbs
{
public:
    LocalPlay(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // LOCALPLAY_H
