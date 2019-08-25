#ifndef SIZE_H
#define SIZE_H
#include "../baseservice.h"
class Size : public BaseService
{
public:
    Size();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // SIZE_H