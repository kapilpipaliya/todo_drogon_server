#ifndef POLICY_H
#define POLICY_H
#include "../baseservice.h"
namespace jadmin {
class Policy : public BaseService
{
public:
    Policy(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // POLICY_H
