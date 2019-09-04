#ifndef DSIZE_H
#define DSIZE_H
#include "../baseservice.h"
namespace jadmin {
class DSize : public BaseService
{
public:
    DSize(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    json del(json event, json args);
};
}
#endif // DSIZE_H
