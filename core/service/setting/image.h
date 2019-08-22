#ifndef IMAGE_H
#define IMAGE_H
#include "../baseservice.h"
class Image : public BaseService
{
public:
    Image(const WebSocketConnectionPtr& wsConnPtr);
    json handleEvent(json event, int next, json args);
    json handleBinaryEvent(json event, int next, std::string &message);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    json thumb_data( json event, json args);
    //Binary functin:
    json save_setting_attachment(json event, std::string &message);
};
#endif // IMAGE_H
