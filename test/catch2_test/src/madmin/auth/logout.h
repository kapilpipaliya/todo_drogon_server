#ifndef LogOut_H
#define LogOut_H

#include "../../wstestbase.h"

namespace madmin {
class LogOut: public WSTestBase
{
  protected:
  void connectToServer();
  void setMessageHandler();
};
}
#endif // LogOut_H
