#ifndef TASK_H
#define TASK_H
#include "../baseservice.h"
class Task : public BaseService
{
public:
    Task();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // TASK_H