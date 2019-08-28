#ifndef MAILER_H
#define MAILER_H


#include "../baseservice.h"
namespace madmin {
class Mailer : public BaseService
{
public:
    Mailer(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // MAILER_H
