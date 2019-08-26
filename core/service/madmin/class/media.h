#ifndef MEDIA_H
#define MEDIA_H


#include "../baseservice.h"
namespace madmin {
class Media : public BaseService
{
public:
    Media();
    void setupTable() override;
};
}
#endif // MEDIA_H
