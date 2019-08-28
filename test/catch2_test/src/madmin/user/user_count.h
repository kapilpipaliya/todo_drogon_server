#ifndef UserCount_H
#define UserCount_H

#include "../../wstestbase.h"

namespace madmin {
class UserCount: public WSTestBase
{
public:
  UserCount(std::string table);
  protected:
  void connectToServer();
  void setMessageHandler();

private:
  std::string table;
};
}
#endif // UserCount_H
