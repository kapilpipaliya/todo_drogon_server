#ifndef TMPPLAYLIST_H
#define TMPPLAYLIST_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class TmpPlayList : public BaseServiceAbs
{
public:
    TmpPlayList(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // TMPPLAYLIST_H
