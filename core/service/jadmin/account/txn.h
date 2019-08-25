#ifndef TXN_H
#define TXN_H
#include "../baseservice.h"
class Txn : public BaseService
{
public:
    Txn();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    json del(json event, json args);
};
#endif // TXN_H
