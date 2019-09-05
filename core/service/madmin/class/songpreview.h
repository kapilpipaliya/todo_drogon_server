#ifndef SONGPREVIEW_H
#define SONGPREVIEW_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class SongPreview : public BaseServiceAbs
{
public:
    SongPreview(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // SONGPREVIEW_H
