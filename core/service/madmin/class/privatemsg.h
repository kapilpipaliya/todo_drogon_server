#ifndef PRIVATEMSG_H
#define PRIVATEMSG_H


#include "../baseservice.h"
namespace madmin {
class PrivateMsg : public BaseService
{
public:
    PrivateMsg();
    void setupTable() override;
};
}
#endif // PRIVATEMSG_H
