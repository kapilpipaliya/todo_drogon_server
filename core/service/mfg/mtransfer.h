#ifndef MTRANSFER_H
#define MTRANSFER_H
#include "../baseservice.h"
class MTransfer : public BaseService
{
public:
    MTransfer(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // MTRANSFER_H
