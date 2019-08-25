#ifndef REQUIRELOGIN_H
#define REQUIRELOGIN_H

#include "../wstestbase.h"

class FormatCheck: public WSTestBase
{
  protected:
  void connectToServer();
  void setMessageHandler();
};

#endif // REQUIRELOGIN_H
