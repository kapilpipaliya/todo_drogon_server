#ifndef SHAPE_H
#define SHAPE_H
#include "../baseservice.h"
class Shape : public BaseService
{
public:
    Shape();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // SHAPE_H