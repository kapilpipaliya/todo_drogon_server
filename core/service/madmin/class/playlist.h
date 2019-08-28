#ifndef PLAYLIST_H
#define PLAYLIST_H


#include "../baseservice.h"
namespace madmin {
class PlayList : public BaseService
{
public:
    PlayList(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // PLAYLIST_H
