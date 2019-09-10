#ifndef RBAC_TODOROLE_H
#define RBAC_TODOROLE_H


#include <vector>
using namespace std;

namespace RBAC { class TodoTask; } 

namespace RBAC {

class TodoRole {
  private:
    vector<TodoTask> task;

};

} // namespace RBAC
#endif
