#ifndef ACCOUNTHEADING_H
#define ACCOUNTHEADING_H
#include "../baseservice.h"
class AccountHeading : public BaseService
{
public:
    AccountHeading();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // ACCOUNTHEADING_H