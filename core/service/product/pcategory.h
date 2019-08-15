#ifndef PCATEGORY_H
#define PCATEGORY_H
#include "../baseservice.h"
class PCategory : public BaseService
{
public:
    PCategory(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // PCATEGORY_H
