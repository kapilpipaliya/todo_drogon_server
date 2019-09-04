#ifndef METAL_H
#define METAL_H
#include "../baseservice.h"
namespace jadmin {
class Metal : public BaseService
{
public:
    Metal(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // METAL_H