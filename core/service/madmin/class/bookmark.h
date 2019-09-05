#ifndef BOOKMARK_H
#define BOOKMARK_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Bookmark : public BaseServiceAbs
{
public:
    Bookmark(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // BOOKMARK_H
