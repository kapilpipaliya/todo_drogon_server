#ifndef PREFERENCE_H
#define PREFERENCE_H


#include "../baseservice.h"
namespace madmin {
class Preference : public BaseService
{
public:
    Preference();
    void setupTable() override;
};
}
#endif // PREFERENCE_H
