#ifndef IMAGE_H
#define IMAGE_H
#include "../baseservice.h"
class Image : public BaseService
{
public:
    Image();
    json handleEvent(json event, int next, json args);

private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);

};
#endif // IMAGE_H
