#ifndef BROWSE_H
#define BROWSE_H


#include "../baseservice.h"
namespace madmin {
class Browse : public BaseService
{
public:
    Browse();
    void setupTable() override;
};
}
#endif // BROWSE_H
