#ifndef LOCALPLAYBASE_H
#define LOCALPLAYBASE_H


#include "../baseservice.h"
namespace madmin {
class LocalPlayBase : public BaseService
{
public:
    LocalPlayBase();
    void setupTable() override;
};
}
#endif // LOCALPLAYBASE_H
