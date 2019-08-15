#ifndef POST_H
#define POST_H
#include "../baseservice.h"
class Post1 : public BaseService
{
public:
    Post1(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // POST_H
