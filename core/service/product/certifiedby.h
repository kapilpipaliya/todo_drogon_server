#ifndef CERTIFIEDBY_H
#define CERTIFIEDBY_H
#include "../baseservice.h"
class CertifiedBy : public BaseService
{
public:
    CertifiedBy(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // CERTIFIEDBY_H
