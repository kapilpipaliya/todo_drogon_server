#ifndef CURRENCY_H
#define CURRENCY_H
#include "../baseservice.h"
namespace jadmin {
class Currency : public BaseService
{
public:
    Currency(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // CURRENCY_H
