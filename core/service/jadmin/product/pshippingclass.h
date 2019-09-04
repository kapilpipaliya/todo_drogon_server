#ifndef PSHIPPINGCLASS_H
#define PSHIPPINGCLASS_H
#include "../baseservice.h"
namespace jadmin {
class PShippingClass : public BaseService
{
public:
    PShippingClass(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // PSHIPPINGCLASS_H
