#ifndef CATALOG_H
#define CATALOG_H


#include "../baseservice.h"
namespace madmin {
class Catalog : public BaseService
{
public:
    Catalog();
    void setupTable() override;
};
}
#endif // CATALOG_H
