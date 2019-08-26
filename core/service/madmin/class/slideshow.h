#ifndef SLIDESHOW_H
#define SLIDESHOW_H


#include "../baseservice.h"
namespace madmin {
class Slideshow : public BaseService
{
public:
    Slideshow();
    void setupTable() override;
};
}
#endif // SLIDESHOW_H
