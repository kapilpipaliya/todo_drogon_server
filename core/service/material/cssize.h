#ifndef CSSIZE_H
#define CSSIZE_H
#include "../baseservice.h"
class CSSize : public BaseService
{
public:
    CSSize();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    json del(json event, json args);
};
#endif // CSSIZE_H
