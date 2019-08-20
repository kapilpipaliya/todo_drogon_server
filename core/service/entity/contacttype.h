#ifndef CONTACTTYPE_H
#define CONTACTTYPE_H
#include "../baseservice.h"
class ContactType : public BaseService
{
public:
    ContactType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // CONTACTTYPE_H