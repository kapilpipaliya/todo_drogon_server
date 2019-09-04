#ifndef TXN_H
#define TXN_H
#include "../baseservice.h"
namespace jadmin {
class Txn : public BaseService
{
public:
    Txn(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    json del(json event, json args);
};
}
#endif // TXN_H
