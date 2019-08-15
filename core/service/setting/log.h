#ifndef LOG_H
#define LOG_H
#include "../baseservice.h"
class Log : public BaseService
{
public:
    Log(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // LOG_H
