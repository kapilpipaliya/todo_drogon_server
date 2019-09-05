#ifndef CSCOLOR_H
#define CSCOLOR_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class CSColor : public BaseServiceAbs
{
public:
    CSColor(JAdminContextPtr );
private:
    void setupTable() override;
    json ins(json event, json args) override;
    json upd(json event, json args) override;
    JAdminContextPtr context;
};
}
#endif // CSCOLOR_H