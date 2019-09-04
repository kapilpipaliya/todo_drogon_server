#ifndef LOG_H
#define LOG_H
#include "../baseservice.h"
namespace jadmin {
class Log : public BaseService
{
public:
    Log(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // LOG_H
