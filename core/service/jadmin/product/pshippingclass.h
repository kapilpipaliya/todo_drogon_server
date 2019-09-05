#ifndef PSHIPPINGCLASS_H
#define PSHIPPINGCLASS_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
typedef std::shared_ptr<JAdminContext> JAdminContextPtr;
namespace jadmin {
class PShippingClass : public BaseServiceAbs
{
public:
    PShippingClass(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    JAdminContextPtr context;
};
}
#endif // PSHIPPINGCLASS_H
