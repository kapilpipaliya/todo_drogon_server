#ifndef RATING_H
#define RATING_H


#include "../baseservice.h"
namespace madmin {
class Rating : public BaseService
{
public:
    Rating(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // RATING_H
