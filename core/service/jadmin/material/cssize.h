#ifndef CSSIZE_H
#define CSSIZE_H
#include "../baseservice.h"
namespace jadmin {
class CSSize : public BaseService
{
public:
    CSSize(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    json del(json event, json args);
};
}
#endif // CSSIZE_H
