#ifndef REFINING_H
#define REFINING_H
#include "../baseservice.h"
namespace jadmin {
class Refining : public BaseService
{
public:
    Refining(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // REFINING_H