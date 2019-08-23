#ifndef CURRENCY_H
#define CURRENCY_H
#include "../baseservice.h"
class Currency : public BaseService
{
public:
    Currency();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // CURRENCY_H
