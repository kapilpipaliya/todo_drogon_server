#ifndef ENTITYTYPE_H
#define ENTITYTYPE_H
#include "../baseservice.h"
namespace jadmin {
class EntityType : public BaseService
{
public:
    EntityType(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // ENTITYTYPE_H