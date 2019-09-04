#ifndef CERTIFIEDBY_H
#define CERTIFIEDBY_H
#include "../baseservice.h"
namespace jadmin {
class CertifiedBy : public BaseService
{
public:
    CertifiedBy(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // CERTIFIEDBY_H
