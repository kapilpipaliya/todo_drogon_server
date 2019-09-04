#ifndef PCATEGORY_H
#define PCATEGORY_H
#include "../baseservice.h"
namespace jadmin {
class PCategory : public BaseService
{
public:
    PCategory(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // PCATEGORY_H
