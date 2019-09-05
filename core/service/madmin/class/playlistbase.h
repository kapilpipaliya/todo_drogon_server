#ifndef PLAYLISTBASE_H
#define PLAYLISTBASE_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class PlayListBase : public BaseServiceAbs
{
public:
    PlayListBase(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // PLAYLISTBASE_H
