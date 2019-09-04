#ifndef CSTYPE_H
#define CSTYPE_H
#include "../baseservice.h"
namespace jadmin {
class CSType : public BaseService
{
public:
    CSType(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // CSTYPE_H