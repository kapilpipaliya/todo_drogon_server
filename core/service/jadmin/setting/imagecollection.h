#ifndef IMAGECOLLECTION_H
#define IMAGECOLLECTION_H
#include "../baseservice.h"
class ImageCollection : public BaseService
{
public:
    ImageCollection();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // IMAGECOLLECTION_H
