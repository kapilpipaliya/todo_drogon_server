#ifndef SEARCH_H
#define SEARCH_H


#include "../baseservice.h"
namespace madmin {
class Search : public BaseService
{
public:
    Search(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // SEARCH_H
