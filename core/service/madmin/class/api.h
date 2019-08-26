#ifndef API_H
#define API_H


#include "../baseservice.h"
namespace madmin {
class Api : public BaseService
{
public:
    Api();
    void setupTable() override;
};
}
#endif // API_H
