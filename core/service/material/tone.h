#ifndef TONE_H
#define TONE_H
#include "../baseservice.h"
class Tone : public BaseService
{
public:
    Tone(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // TONE_H