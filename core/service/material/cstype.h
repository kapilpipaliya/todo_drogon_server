#ifndef CSTYPE_H
#define CSTYPE_H
#include "../baseservice.h"
class CSType : public BaseService
{
public:
    CSType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // CSTYPE_H