#ifndef RANDOM_H
#define RANDOM_H


#include "../baseservice.h"
namespace madmin {
class Random : public BaseService
{
public:
    Random(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // RANDOM_H
