#ifndef ACCESSORY_H
#define ACCESSORY_H
#include "../baseservice.h"
namespace jadmin {
class Accessory : public BaseService
{
public:
    Accessory(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // ACCESSORY_H