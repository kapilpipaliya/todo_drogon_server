#ifndef SHAPE_H
#define SHAPE_H
#include "../baseservice.h"
class Shape : public BaseService
{
public:
    Shape(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // SHAPE_H