#ifndef METALISSUE_H
#define METALISSUE_H
#include "../baseservice.h"
class MetalIssue : public BaseService
{
public:
    MetalIssue(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // METALISSUE_H
