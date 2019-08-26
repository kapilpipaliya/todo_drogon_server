#ifndef USERFLAG_H
#define USERFLAG_H


#include "../baseservice.h"
namespace madmin {
class UserFlag : public BaseService
{
public:
    UserFlag();
    void setupTable() override;
};
}
#endif // USERFLAG_H
