#ifndef IMAGECOLLECTION_H
#define IMAGECOLLECTION_H
#include "../baseservice.h"
class ImageCollection : public BaseService
{
public:
    ImageCollection(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // IMAGECOLLECTION_H
