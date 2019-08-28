#ifndef LOG_H
#define LOG_H


#include "../baseservice.h"
namespace madmin {
class Log : public BaseService
{
public:
    Log(const MAdminContextPtr &);
    void setupTable() override;
};
}
#endif // LOG_H
