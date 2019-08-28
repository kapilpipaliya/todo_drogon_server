#ifndef USERFLAG_H
#define USERFLAG_H


#include "../baseservice.h"
namespace madmin {
class UserFlag : public BaseService
{
public:
    UserFlag(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // USERFLAG_H
