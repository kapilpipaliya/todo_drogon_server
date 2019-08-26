#ifndef PLAYLISTBASE_H
#define PLAYLISTBASE_H


#include "../baseservice.h"
namespace madmin {
class PlayListBase : public BaseService
{
public:
    PlayListBase();
    void setupTable() override;
};
}
#endif // PLAYLISTBASE_H
