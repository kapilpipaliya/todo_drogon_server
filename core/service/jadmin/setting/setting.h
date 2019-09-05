#ifndef SETTING_H
#define SETTING_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
typedef std::shared_ptr<JAdminContext> JAdminContextPtr;
namespace jadmin {
class Setting : public BaseServiceAbs
{
public:
    Setting(const JAdminContextPtr &);

   json handleEvent(json event, int next, json args);

private:
    void setupTable();
    json save(json event, json args);
    json del( json event, json args);
    JAdminContextPtr context;
};
}
#endif // SETTING_H
