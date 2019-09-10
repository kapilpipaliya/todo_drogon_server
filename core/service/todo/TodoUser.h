#ifndef RBAC_TODOUSER_H
#define RBAC_TODOUSER_H


#include <vector>
using namespace std;

namespace RBAC { class TodoRole; } 

namespace RBAC {

class TodoUser {
  private:
    vector<TodoRole> role;


  public:
    //Loop role and find if any role contains task_no
    bool hasPermission(long taskNo);

};

} // namespace RBAC
#endif
