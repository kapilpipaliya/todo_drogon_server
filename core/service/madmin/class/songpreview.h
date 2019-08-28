#ifndef SONGPREVIEW_H
#define SONGPREVIEW_H


#include "../baseservice.h"
namespace madmin {
class SongPreview : public BaseService
{
public:
    SongPreview(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // SONGPREVIEW_H
