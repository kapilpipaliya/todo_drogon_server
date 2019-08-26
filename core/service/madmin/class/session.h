#ifndef SESSION_H
#define SESSION_H


#include "../baseservice.h"
namespace madmin {
class Session : public BaseService
{
public:
    Session();
    void setupTable() override;
};
}
#endif // SESSION_H
