#ifndef PURITY_H
#define PURITY_H
#include "../baseservice.h"
class Purity : public BaseService
{
public:
    Purity(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    json del(json event, json args);
};
#endif // PURITY_H
