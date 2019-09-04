#ifndef CLARITY_H
#define CLARITY_H
#include "../baseservice.h"
namespace jadmin {
class Clarity : public BaseService
{
public:
    Clarity(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // CLARITY_H