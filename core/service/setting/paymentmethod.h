#ifndef PAYMENTMETHOD_H
#define PAYMENTMETHOD_H
#include "../baseservice.h"

class PaymentMethod : public BaseService
{
public:
    PaymentMethod(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // PAYMENTMETHOD_H
