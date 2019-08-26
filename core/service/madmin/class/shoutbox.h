#ifndef SHOUTBOX_H
#define SHOUTBOX_H


#include "../baseservice.h"
namespace madmin {
class ShoutBox : public BaseService
{
public:
    ShoutBox();
    void setupTable() override;
};
}
#endif // SHOUTBOX_H
