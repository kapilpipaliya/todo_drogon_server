#ifndef SETTINGTYPE_H
#define SETTINGTYPE_H
#include "../baseservice.h"
class SettingType : public BaseService
{
public:
    SettingType();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // SETTINGTYPE_H
