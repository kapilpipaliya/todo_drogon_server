#ifndef CLARITY_H
#define CLARITY_H
#include "../baseservice.h"
class Clarity : public BaseService
{
public:
    Clarity(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // CLARITY_H