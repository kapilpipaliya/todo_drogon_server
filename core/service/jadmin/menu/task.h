#ifndef TASK_H
#define TASK_H
#include "../baseservice.h"
namespace jadmin {
class Task : public BaseService
{
public:
    Task(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // TASK_H