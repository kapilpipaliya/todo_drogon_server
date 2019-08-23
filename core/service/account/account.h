#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "../baseservice.h"
class Account : public BaseService
{
public:
    Account();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // ACCOUNT_H
