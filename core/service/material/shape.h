#ifndef SHAPE_H
#define SHAPE_H
#include "../baseservice.h"
class Shape : public BaseService
{
public:
    Shape(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // SHAPE_H