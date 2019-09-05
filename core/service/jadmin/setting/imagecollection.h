#ifndef IMAGECOLLECTION_H
#define IMAGECOLLECTION_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class ImageCollection : public BaseServiceAbs
{
public:
    ImageCollection(JAdminContextPtr );
private:
    void setupTable() override;
    json ins(json event, json args) override;
    json upd(json event, json args) override;
    JAdminContextPtr context;
};
}
#endif // IMAGECOLLECTION_H
