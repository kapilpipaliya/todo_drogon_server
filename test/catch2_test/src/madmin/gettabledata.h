#ifndef GetTableData_H
#define GetTableData_H

#include "../wstestbase.h"

namespace madmin {
class GetTableData: public WSTestBase
{
public:
  GetTableData(std::string table);
  protected:
  void connectToServer();
  void setMessageHandler();

private:
  std::string table;
};
}
#endif // GetTableData_H
