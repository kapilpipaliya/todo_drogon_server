#ifndef MAILER_H
#define MAILER_H


#include "../baseservice.h"
namespace madmin {
class Mailer : public BaseService
{
public:
    Mailer();
    void setupTable() override;
};
}
#endif // MAILER_H
