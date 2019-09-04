#ifndef POST_H
#define POST_H
#include "../baseservice.h"
namespace jadmin {
class Post1 : public BaseService
{
public:
    Post1(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // POST_H
