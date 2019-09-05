#ifndef SIZE_H
#define SIZE_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
typedef std::shared_ptr<JAdminContext> JAdminContextPtr;
namespace jadmin {
class Size : public BaseServiceAbs
{
public:
    Size(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    JAdminContextPtr context;
};
}
#endif // SIZE_H