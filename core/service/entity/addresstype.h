#ifndef ADDRESSTYPE_H
#define ADDRESSTYPE_H
#include "../baseservice.h"
class AddressType : public BaseService
{
public:
    AddressType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // ADDRESSTYPE_H