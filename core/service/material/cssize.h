#ifndef CSSIZE_H
#define CSSIZE_H
#include "../baseservice.h"
class CSSize : public BaseService
{
public:
    CSSize(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
    Json::Value del(Json::Value event, Json::Value args);
};
#endif // CSSIZE_H
