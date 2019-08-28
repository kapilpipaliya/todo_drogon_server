#ifndef SHARE_H
#define SHARE_H


#include "../baseservice.h"
namespace madmin {
class Share : public BaseService
{
public:
    Share(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // SHARE_H
