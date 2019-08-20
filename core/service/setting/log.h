#ifndef LOG_H
#define LOG_H
#include "../baseservice.h"
class Log : public BaseService
{
public:
    Log(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // LOG_H
