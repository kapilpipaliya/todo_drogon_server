#ifndef DSIZE_H
#define DSIZE_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
typedef std::shared_ptr<JAdminContext> JAdminContextPtr;
namespace jadmin {
class DSize : public BaseServiceAbs
{
public:
    DSize(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    json del(json event, json args);
    JAdminContextPtr context;
};
}
#endif // DSIZE_H
