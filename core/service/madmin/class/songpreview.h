#ifndef SONGPREVIEW_H
#define SONGPREVIEW_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class SongPreview : public BaseServiceAbs
{
public:
    SongPreview(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // SONGPREVIEW_H
