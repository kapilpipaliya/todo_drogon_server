#ifndef CONTACTTYPE_H
#define CONTACTTYPE_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
typedef std::shared_ptr<JAdminContext> JAdminContextPtr;
namespace jadmin {
class ContactType : public BaseServiceAbs
{
public:
    ContactType(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    JAdminContextPtr context;
};
}
#endif // CONTACTTYPE_H