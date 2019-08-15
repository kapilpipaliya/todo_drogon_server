#ifndef MFGTXN_H
#define MFGTXN_H
#include "../baseservice.h"
class MfgTxn : public BaseService
{
public:
    MfgTxn(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // MFGTXN_H
