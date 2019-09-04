#ifndef ACCOUNTTYPE_H
#define ACCOUNTTYPE_H
#include "../baseservice.h"
namespace jadmin {
class AccountType : public BaseService
{
public:
    AccountType(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // ACCOUNTTYPE_H
