#ifndef SETTING_H
#define SETTING_H

#include "../baseservice.h"

class Setting : public BaseService
{
public:
    Setting();

   json handleEvent(json event, int next, json args);

private:
    void setupTable();
    json ins(json event, json args){};
    json upd(json event, json args){};
    json save(json event, json args);
    json del( json event, json args);
};
#endif // SETTING_H
