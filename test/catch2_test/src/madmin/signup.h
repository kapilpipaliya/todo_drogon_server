#ifndef SignUp_H
#define SignUp_H

#include "../wstestbase.h"

namespace madmin {
class SignUp: public WSTestBase
{
protected:
  void connectToServer();
  void setMessageHandler();
};
}
#endif // SignUp_H
