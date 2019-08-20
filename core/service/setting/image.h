#ifndef IMAGE_H
#define IMAGE_H
#include "../baseservice.h"
class Image : public BaseService
{
public:
    Image(const WebSocketConnectionPtr& wsConnPtr);
    Json::Value handleEvent(Json::Value event, int next, Json::Value args);
    Json::Value handleBinaryEvent(Json::Value event, int next, std::string &message);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
    Json::Value thumb_data( Json::Value event, Json::Value args);
    //Binary functin:
    Json::Value save_setting_attachment(Json::Value event, std::string &message);
};
#endif // IMAGE_H
