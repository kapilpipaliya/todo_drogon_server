#ifndef PasswordChange_H
#define PasswordChange_H

#include "../../wstestbase.h"

namespace madmin {
class PasswordChange: public WSTestBase
{
  protected:
  void connectToServer();
  void setMessageHandler();
};
}
#endif // PasswordChange_H
