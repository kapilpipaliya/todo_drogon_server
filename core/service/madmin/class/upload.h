#ifndef UPLOAD_H
#define UPLOAD_H

#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/madmincontext.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Upload : public BaseServiceAbs
{
public:
    Upload(MAdminContextPtr );
    void setupTable() override;
private:
    MAdminContextPtr context;
};
}
#endif // UPLOAD_H
