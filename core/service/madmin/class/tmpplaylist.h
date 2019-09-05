#ifndef TMPPLAYLIST_H
#define TMPPLAYLIST_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class TmpPlayList : public BaseServiceAbs
{
public:
    TmpPlayList(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // TMPPLAYLIST_H
