#ifndef WAXSETTING_H
#define WAXSETTING_H
#include "../baseservice.h"
namespace jadmin {
class WaxSetting : public BaseService
{
public:
    WaxSetting(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // WAXSETTING_H