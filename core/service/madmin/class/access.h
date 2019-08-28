#ifndef ACCESS_H
#define ACCESS_H


#include "../baseservice.h"
namespace madmin {
class Access : public BaseService
{
public:
    Access(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // ACCESS_H
