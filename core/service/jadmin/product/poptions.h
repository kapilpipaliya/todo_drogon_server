#ifndef POPTIONS_H
#define POPTIONS_H
#include "../baseservice.h"
namespace jadmin {
class POption : public BaseService
{
public:
    POption(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // POPTIONS_H
