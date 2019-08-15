#ifndef CSCOLOR_H
#define CSCOLOR_H
#include "../baseservice.h"
class CSColor : public BaseService
{
public:
    CSColor(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // CSCOLOR_H