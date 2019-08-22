#ifndef POPTIONS_H
#define POPTIONS_H
#include "../baseservice.h"
class POption : public BaseService
{
public:
    POption(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // POPTIONS_H
