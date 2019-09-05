#ifndef CSSIZE_H
#define CSSIZE_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class CSSize : public BaseServiceAbs
{
public:
    CSSize(JAdminContextPtr );
private:
    void setupTable() override;
    json ins(json event, json args) override;
    json upd(json event, json args) override;
    json del(json event, json args) override;
    JAdminContextPtr context;
};
}
#endif // CSSIZE_H
