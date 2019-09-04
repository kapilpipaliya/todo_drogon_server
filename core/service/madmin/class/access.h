#pragma once

#include "../baseservice.h"
namespace madmin {
class Access : public BaseService
{
public:
    Access(const MAdminContextPtr &);
    void setupTable() override;
};
}
