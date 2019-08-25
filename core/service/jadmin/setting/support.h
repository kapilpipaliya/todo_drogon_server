#ifndef SUPPORT_H
#define SUPPORT_H

#include "../baseservice.h"

class Support : public BaseService
{
public:
    Support();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};

#endif // SUPPORT_H
