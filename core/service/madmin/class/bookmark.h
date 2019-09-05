#ifndef BOOKMARK_H
#define BOOKMARK_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;
namespace madmin {
class Bookmark : public BaseServiceAbs
{
public:
    Bookmark(const MAdminContextPtr &);
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // BOOKMARK_H
