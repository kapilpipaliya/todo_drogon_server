#pragma once

#include "../baseservice.h"
namespace jadmin {
class Support : public BaseService
{
public:
    Support(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
