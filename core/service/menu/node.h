#ifndef NODE_H
#define NODE_H
#include "../baseservice.h"
class Node : public BaseService
{
public:
    Node(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // NODE_H