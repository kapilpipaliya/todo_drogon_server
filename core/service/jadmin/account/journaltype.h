#ifndef JOURNALTYPE_H
#define JOURNALTYPE_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
typedef std::shared_ptr<JAdminContext> JAdminContextPtr;
namespace jadmin {
class JournalType : public BaseServiceAbs
{
public:
    JournalType(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    JAdminContextPtr context;
};
}
#endif // JOURNALTYPE_H