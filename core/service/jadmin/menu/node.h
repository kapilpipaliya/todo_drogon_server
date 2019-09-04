#ifndef NODE_H
#define NODE_H
#include "../baseservice.h"
namespace jadmin {
class Node : public BaseService
{
public:
    Node(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // NODE_H
