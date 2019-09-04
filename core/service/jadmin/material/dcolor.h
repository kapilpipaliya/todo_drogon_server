#ifndef DCOLOR_H
#define DCOLOR_H
#include "../baseservice.h"
namespace jadmin {
class DColor : public BaseService
{
public:
    DColor(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // DCOLOR_H