#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class PlayList : public BaseServiceAbs
{
public:
    PlayList(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // PLAYLIST_H
