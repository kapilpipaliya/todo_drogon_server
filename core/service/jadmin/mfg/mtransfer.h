#ifndef MTRANSFER_H
#define MTRANSFER_H
#include "../baseservice.h"
namespace jadmin {
class MTransfer : public BaseService
{
public:
    MTransfer(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // MTRANSFER_H
