#ifndef WAXSETTING_H
#define WAXSETTING_H
#include "../baseservice.h"
class WaxSetting : public BaseService
{
public:
    WaxSetting(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // WAXSETTING_H