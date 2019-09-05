#ifndef PLAYLISTBASE_H
#define PLAYLISTBASE_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class PlayListBase : public BaseServiceAbs
{
public:
    PlayListBase(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // PLAYLISTBASE_H
