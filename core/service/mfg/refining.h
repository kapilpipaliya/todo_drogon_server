#ifndef REFINING_H
#define REFINING_H
#include "../baseservice.h"
class Refining : public BaseService
{
public:
    Refining(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // REFINING_H