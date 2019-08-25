#ifndef CSTYPE_H
#define CSTYPE_H
#include "../baseservice.h"
class CSType : public BaseService
{
public:
    CSType();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // CSTYPE_H