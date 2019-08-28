#ifndef UPDATE_H
#define UPDATE_H


#include "../baseservice.h"
namespace madmin {
class Update : public BaseService
{
public:
    Update(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // UPDATE_H
