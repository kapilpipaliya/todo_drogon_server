#ifndef RECOMMANDATION_H
#define RECOMMANDATION_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class Recommandation : public BaseServiceAbs
{
public:
    Recommandation(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // RECOMMANDATION_H
