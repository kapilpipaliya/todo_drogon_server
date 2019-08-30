#ifndef CreateUser_H
#define CreateUser_H

#include "../../wstestbase.h"

namespace madmin {
class CreateUser: public WSTestBase
{
public:
  CreateUser(std::string table, std::string insert_query, std::string update_query, std::string delete_query);

  protected:
  void connectToServer();
  void setMessageHandler();

private:
  std::string table;
  std::string insert_query;
  std::string update_query;
  std::string delete_query;
};
}
#endif // CreateUser_H
