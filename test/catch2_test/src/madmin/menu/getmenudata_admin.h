#ifndef GetMenuAdmin_H
#define GetMenuAdmin_H

#include "../../wstestbase.h"

namespace madmin {
class GetMenuAdmin: public WSTestBase
{
public:
  GetMenuAdmin(std::string table);
  protected:
  void connectToServer();
  void setMessageHandler();

private:
  std::string table;
};
}
#endif // GetMenuAdmin_H
