#ifndef PURITY_H
#define PURITY_H
#include "../baseservice.h"
namespace jadmin {
class Purity : public BaseService
{
public:
    Purity(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    json del(json event, json args);
};
}
#endif // PURITY_H
