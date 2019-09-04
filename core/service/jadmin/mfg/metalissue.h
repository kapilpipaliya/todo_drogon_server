#ifndef METALISSUE_H
#define METALISSUE_H
#include "../baseservice.h"
namespace jadmin {
class MetalIssue : public BaseService
{
public:
    MetalIssue(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // METALISSUE_H
