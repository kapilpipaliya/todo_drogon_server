#ifndef TAG_H
#define TAG_H
#include "../baseservice.h"
class Tag : public BaseService
{
public:
    Tag(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // TAG_H
