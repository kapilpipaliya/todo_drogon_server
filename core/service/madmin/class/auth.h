#ifndef AUTH_H
#define AUTH_H


#include "../baseservice.h"
namespace madmin {
class Auth : public BaseService
{
public:
    Auth();
    void setupTable() override;
};
}
#endif // AUTH_H
