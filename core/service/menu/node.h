#ifndef NODE_H
#define NODE_H
#include "../baseservice.h"
class Node : public BaseService
{
public:
    Node();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // NODE_H