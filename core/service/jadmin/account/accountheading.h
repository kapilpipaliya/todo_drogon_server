#ifndef ACCOUNTHEADING_H
#define ACCOUNTHEADING_H
#include "../baseservice.h"
namespace jadmin {
class AccountHeading : public BaseService
{
public:
    AccountHeading(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // ACCOUNTHEADING_H