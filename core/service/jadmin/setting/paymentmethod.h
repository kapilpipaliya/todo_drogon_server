#ifndef PAYMENTMETHOD_H
#define PAYMENTMETHOD_H
#include "../baseservice.h"
namespace jadmin {
class PaymentMethod : public BaseService
{
public:
    PaymentMethod(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // PAYMENTMETHOD_H
