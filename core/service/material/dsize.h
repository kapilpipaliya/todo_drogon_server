#ifndef DSIZE_H
#define DSIZE_H
#include "../baseservice.h"
class DSize : public BaseService
{
public:
    DSize(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
    Json::Value del(Json::Value event, Json::Value args);
};
#endif // DSIZE_H
