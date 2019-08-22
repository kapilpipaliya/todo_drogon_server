#ifndef JOURNALTYPE_H
#define JOURNALTYPE_H
#include "../baseservice.h"
class JournalType : public BaseService
{
public:
    JournalType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // JOURNALTYPE_H