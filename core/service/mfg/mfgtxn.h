#ifndef MFGTXN_H
#define MFGTXN_H
#include "../baseservice.h"
class MfgTxn : public BaseService
{
public:
    MfgTxn(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // MFGTXN_H
