#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class PlayList : public BaseServiceAbs
{
public:
    PlayList(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // PLAYLIST_H
