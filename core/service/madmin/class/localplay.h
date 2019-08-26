#ifndef LOCALPLAY_H
#define LOCALPLAY_H


#include "../baseservice.h"
namespace madmin {
class LocalPlay : public BaseService
{
public:
    LocalPlay();
    void setupTable() override;
};
}
#endif // LOCALPLAY_H
