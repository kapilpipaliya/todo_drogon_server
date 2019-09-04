#ifndef ADDRESSTYPE_H
#define ADDRESSTYPE_H
#include "../baseservice.h"
namespace jadmin {
class AddressType : public BaseService
{
public:
    AddressType(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // ADDRESSTYPE_H