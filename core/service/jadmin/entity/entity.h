#ifndef ENTITY_H
#define ENTITY_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
typedef std::shared_ptr<JAdminContext> JAdminContextPtr;
namespace jadmin {
class Entity : public BaseServiceAbs
{
public:
    Entity(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    json del(json event, json args);
    JAdminContextPtr context;
};
}
#endif // ENTITY_H
