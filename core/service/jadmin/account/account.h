#pragma once
#include "../baseservice.h"
namespace jadmin {
class Account : public BaseService
{
public:
    Account(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
