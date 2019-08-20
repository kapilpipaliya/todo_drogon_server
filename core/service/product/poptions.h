#ifndef POPTIONS_H
#define POPTIONS_H
#include "../baseservice.h"
class POption : public BaseService
{
public:
    POption(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // POPTIONS_H
