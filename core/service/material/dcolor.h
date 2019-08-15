#ifndef DCOLOR_H
#define DCOLOR_H
#include "../baseservice.h"
class DColor : public BaseService
{
public:
    DColor(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // DCOLOR_H