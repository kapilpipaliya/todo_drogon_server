#ifndef ARTIST_H
#define ARTIST_H


#include "../baseservice.h"
namespace madmin {
class Artist : public BaseService
{
public:
    Artist();
    void setupTable() override;
};
}
#endif // ARTIST_H
