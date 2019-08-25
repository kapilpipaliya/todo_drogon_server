#ifndef LogIn_H
#define LogIn_H

#include "../wstestbase.h"

class LogIn: public WSTestBase
{
  protected:
  void connectToServer();
  void setMessageHandler();
};

#endif // LogIn_H
