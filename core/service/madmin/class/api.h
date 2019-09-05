#ifndef API_H
#define API_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class Api : public BaseServiceAbs
{
public:
    Api(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // API_H
