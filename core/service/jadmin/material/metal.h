#ifndef METAL_H
#define METAL_H
#include "../baseservice.h"
class Metal : public BaseService
{
public:
    Metal();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // METAL_H