#ifndef METALISSUE_H
#define METALISSUE_H
#include "../baseservice.h"
class MetalIssue : public BaseService
{
public:
    MetalIssue(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // METALISSUE_H
