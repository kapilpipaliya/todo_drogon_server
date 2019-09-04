#ifndef CSCOLOR_H
#define CSCOLOR_H
#include "../baseservice.h"
namespace jadmin {
class CSColor : public BaseService
{
public:
    CSColor(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // CSCOLOR_H