#ifndef MFGTXN_H
#define MFGTXN_H
#include "../baseservice.h"
namespace jadmin {
class MfgTxn : public BaseService
{
public:
    MfgTxn(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // MFGTXN_H
