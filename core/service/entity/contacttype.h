#ifndef CONTACTTYPE_H
#define CONTACTTYPE_H
#include "../baseservice.h"
class ContactType : public BaseService
{
public:
    ContactType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // CONTACTTYPE_H