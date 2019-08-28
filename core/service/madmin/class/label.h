#ifndef LABEL_H
#define LABEL_H


#include "../baseservice.h"
namespace madmin {
class Label : public BaseService
{
public:
    Label(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // LABEL_H
