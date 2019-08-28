#ifndef CreateUser_H
#define CreateUser_H

#include "../../wstestbase.h"

namespace madmin {
class CreateUser: public WSTestBase
{
public:
  CreateUser(std::string table);
  protected:
  void connectToServer();
  void setMessageHandler();

private:
  std::string table;
};
}
#endif // CreateUser_H
