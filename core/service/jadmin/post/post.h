#ifndef POST_H
#define POST_H
#include "../baseservice.h"
class Post1 : public BaseService
{
public:
    Post1();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // POST_H
