#ifndef LOG_H
#define LOG_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
typedef std::shared_ptr<JAdminContext> JAdminContextPtr;
namespace jadmin {
class Log : public BaseServiceAbs
{
public:
    Log(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    JAdminContextPtr context;
};
}
#endif // LOG_H
