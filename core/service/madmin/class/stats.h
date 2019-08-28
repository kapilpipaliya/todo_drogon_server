#ifndef STATS_H
#define STATS_H


#include "../baseservice.h"
namespace madmin {
class Stats : public BaseService
{
public:
    Stats(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // STATS_H
