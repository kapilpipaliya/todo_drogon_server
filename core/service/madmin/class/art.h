#ifndef ART_H
#define ART_H


#include "../baseservice.h"
namespace madmin {
class Art : public BaseService
{
public:
    Art();
    void setupTable() override;
};
}
#endif // ART_H
