#ifndef CERTIFIEDBY_H
#define CERTIFIEDBY_H
#include "../baseservice.h"
class CertifiedBy : public BaseService
{
public:
    CertifiedBy();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // CERTIFIEDBY_H
