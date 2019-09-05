#ifndef IMAGE_H
#define IMAGE_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
typedef std::shared_ptr<JAdminContext> JAdminContextPtr;
namespace jadmin {
class Image : public BaseServiceAbs
{
public:
    Image(const JAdminContextPtr &);
    json handleEvent(json event, int next, json args);

private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    JAdminContextPtr context;

};
}
#endif // IMAGE_H
