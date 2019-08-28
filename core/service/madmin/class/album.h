#ifndef ALBUM_H
#define ALBUM_H


#include "../baseservice.h"
namespace madmin {
class Album : public BaseService
{
public:
    Album(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // ALBUM_H
