#ifndef POPTIONS_H
#define POPTIONS_H
#include "../baseservice.h"
class POption : public BaseService
{
public:
    POption(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // POPTIONS_H
