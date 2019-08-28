#ifndef GetTableDataAdmin_H
#define GetTableDataAdmin_H

#include "../wstestbase.h"

namespace madmin {
class GetTableDataAdmin: public WSTestBase
{
public:
  GetTableDataAdmin(std::string table);
  protected:
  void connectToServer();
  void setMessageHandler();

private:
  std::string table;
};
}
#endif // GetTableDataAdmin_H
