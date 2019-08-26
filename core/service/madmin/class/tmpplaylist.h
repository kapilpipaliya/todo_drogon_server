#ifndef TMPPLAYLIST_H
#define TMPPLAYLIST_H


#include "../baseservice.h"
namespace madmin {
class TmpPlayList : public BaseService
{
public:
    TmpPlayList();
    void setupTable() override;
};
}
#endif // TMPPLAYLIST_H
