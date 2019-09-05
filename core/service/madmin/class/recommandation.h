#ifndef RECOMMANDATION_H
#define RECOMMANDATION_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Recommandation : public BaseServiceAbs
{
public:
    Recommandation(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // RECOMMANDATION_H
