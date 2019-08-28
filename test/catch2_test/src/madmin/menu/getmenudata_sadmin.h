#ifndef GetMenuSAdmin_H
#define GetMenuSAdmin_H

#include "../../wstestbase.h"

namespace madmin {
class GetMenuSAdmin: public WSTestBase
{
public:
  GetMenuSAdmin(std::string table);
  protected:
  void connectToServer();
  void setMessageHandler();

private:
  std::string table;
};
}
#endif // GetMenuSAdmin_H
