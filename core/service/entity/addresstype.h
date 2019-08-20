#ifndef ADDRESSTYPE_H
#define ADDRESSTYPE_H
#include "../baseservice.h"
class AddressType : public BaseService
{
public:
    AddressType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // ADDRESSTYPE_H