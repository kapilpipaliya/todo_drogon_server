#ifndef AUTHCHECK_H
#define AUTHCHECK_H

#include "../wstestbase.h"

namespace madmin {
class AuthCheck: public WSTestBase
{
public:
  protected:
  void connectToServer();
  void setMessageHandler();
};
}
#endif // AUTHCHECK_H
