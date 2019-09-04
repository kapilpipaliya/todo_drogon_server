#ifndef CASTING_H
#define CASTING_H
#include "../baseservice.h"
namespace jadmin {
class Casting : public BaseService
{
public:
    Casting(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // CASTING_H