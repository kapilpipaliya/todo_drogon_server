#ifndef ROLE_H
#define ROLE_H
#include "../baseservice.h"
class Role : public BaseService
{
public:
    Role();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // ROLE_H