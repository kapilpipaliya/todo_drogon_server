#ifndef TONE_H
#define TONE_H
#include "../baseservice.h"
class Tone : public BaseService
{
public:
    Tone(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // TONE_H