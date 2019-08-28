#ifndef BROWSE_H
#define BROWSE_H


#include "../baseservice.h"
namespace madmin {
class Browse : public BaseService
{
public:
    Browse(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // BROWSE_H
