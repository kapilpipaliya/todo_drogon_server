#ifndef RANDOM_H
#define RANDOM_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Random : public BaseServiceAbs
{
public:
    Random(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // RANDOM_H
