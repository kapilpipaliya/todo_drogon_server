#ifndef PSHIPPINGCLASS_H
#define PSHIPPINGCLASS_H
#include "../baseservice.h"
class PShippingClass : public BaseService
{
public:
    PShippingClass(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // PSHIPPINGCLASS_H
