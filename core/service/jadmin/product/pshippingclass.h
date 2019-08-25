#ifndef PSHIPPINGCLASS_H
#define PSHIPPINGCLASS_H
#include "../baseservice.h"
class PShippingClass : public BaseService
{
public:
    PShippingClass();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // PSHIPPINGCLASS_H
