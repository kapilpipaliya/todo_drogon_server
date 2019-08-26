#ifndef USERACTIVITY_H
#define USERACTIVITY_H


#include "../baseservice.h"
namespace madmin {
class UserActivity : public BaseService
{
public:
    UserActivity();
    void setupTable() override;
};
}
#endif // USERACTIVITY_H
