#ifndef SEARCH_H
#define SEARCH_H


#include "../baseservice.h"
namespace madmin {
class Search : public BaseService
{
public:
    Search();
    void setupTable() override;
};
}
#endif // SEARCH_H
