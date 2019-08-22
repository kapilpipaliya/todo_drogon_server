#ifndef CONTACTTYPE_H
#define CONTACTTYPE_H
#include "../baseservice.h"
class ContactType : public BaseService
{
public:
    ContactType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // CONTACTTYPE_H