#ifndef SIZE_H
#define SIZE_H
#include "../baseservice.h"
class Size : public BaseService
{
public:
    Size(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // SIZE_H