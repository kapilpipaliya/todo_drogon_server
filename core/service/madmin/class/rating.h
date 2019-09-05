#ifndef RATING_H
#define RATING_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class Rating : public BaseServiceAbs
{
public:
    Rating(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // RATING_H
