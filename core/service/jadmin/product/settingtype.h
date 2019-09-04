#pragma once
#include "../baseservice.h"
namespace jadmin {
class SettingType : public BaseService
{
public:
    SettingType(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
