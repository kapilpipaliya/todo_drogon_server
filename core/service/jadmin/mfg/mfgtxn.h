#ifndef MFGTXN_H
#define MFGTXN_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class MfgTxn : public BaseServiceAbs
{
public:
    MfgTxn(JAdminContextPtr );
private:
    void setupTable() override;
    json ins(json event, json args) override;
    json upd(json event, json args) override;
    JAdminContextPtr context;
};
}
#endif // MFGTXN_H
