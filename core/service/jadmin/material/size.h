#ifndef SIZE_H
#define SIZE_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class Size : public BaseServiceAbs
{
public:
    Size(JAdminContextPtr );
private:
    void setupTable() override;
    json ins(json event, json args) override;
    json upd(json event, json args) override;
    JAdminContextPtr context;
};
}
#endif // SIZE_H