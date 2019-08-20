#ifndef CSTYPE_H
#define CSTYPE_H
#include "../baseservice.h"
class CSType : public BaseService
{
public:
    CSType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // CSTYPE_H