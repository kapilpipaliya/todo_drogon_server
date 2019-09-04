#ifndef TAG_H
#define TAG_H
#include "../baseservice.h"
namespace jadmin {
class Tag : public BaseService
{
public:
    Tag(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // TAG_H
