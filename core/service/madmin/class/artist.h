#ifndef ARTIST_H
#define ARTIST_H


#include "../baseservice.h"
namespace madmin {
class Artist : public BaseService
{
public:
    Artist(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // ARTIST_H
