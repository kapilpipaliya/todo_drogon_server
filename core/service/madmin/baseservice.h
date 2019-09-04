#pragma once

#include "../baseserviceabs.h"
#include "../../../wscontroller/context/madmincontext.h"
namespace madmin {

typedef std::shared_ptr<MAdminContext> MAdminContextPtr;

class BaseService : public BaseServiceAbs
{
public:
    BaseService(const MAdminContextPtr &context_);
    virtual ~BaseService();
    MAdminContextPtr context;
};

}
