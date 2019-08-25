#ifndef AUTHCHECK_H
#define AUTHCHECK_H

#include "../wstestbase.h"

class AuthCheck: public WSTestBase
{
public:
  protected:
  void connectToServer();
  void setMessageHandler();
};

#endif // AUTHCHECK_H
