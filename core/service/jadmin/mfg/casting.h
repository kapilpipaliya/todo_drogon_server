#ifndef CASTING_H
#define CASTING_H
#include "../baseservice.h"
class Casting : public BaseService
{
public:
    Casting();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // CASTING_H