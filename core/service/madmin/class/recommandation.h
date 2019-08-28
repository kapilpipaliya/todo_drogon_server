#ifndef RECOMMANDATION_H
#define RECOMMANDATION_H


#include "../baseservice.h"
namespace madmin {
class Recommandation : public BaseService
{
public:
    Recommandation(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // RECOMMANDATION_H
