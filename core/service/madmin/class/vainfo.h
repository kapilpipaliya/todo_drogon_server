#ifndef VAINFO_H
#define VAINFO_H


#include "../baseservice.h"
namespace madmin {
class VaInfo : public BaseService
{
public:
    VaInfo(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // VAINFO_H
