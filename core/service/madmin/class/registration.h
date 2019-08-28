#ifndef REGISTRATION_H
#define REGISTRATION_H


#include "../baseservice.h"
namespace madmin {
class Registration : public BaseService
{
public:
    Registration(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // REGISTRATION_H
