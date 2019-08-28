#ifndef SONG_H
#define SONG_H


#include "../baseservice.h"
namespace madmin {
class Song : public BaseService
{
public:
    Song(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // SONG_H
