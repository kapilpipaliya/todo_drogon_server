#ifndef BOOKMARK_H
#define BOOKMARK_H


#include "../baseservice.h"
namespace madmin {
class Bookmark : public BaseService
{
public:
    Bookmark();
    void setupTable() override;
};
}
#endif // BOOKMARK_H
