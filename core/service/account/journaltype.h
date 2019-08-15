#ifndef JOURNALTYPE_H
#define JOURNALTYPE_H
#include "../baseservice.h"
class JournalType : public BaseService
{
public:
    JournalType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // JOURNALTYPE_H