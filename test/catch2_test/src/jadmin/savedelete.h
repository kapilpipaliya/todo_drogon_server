#ifndef SaveDelete_H
#define SaveDelete_H

#include "../wstestbase.h"

namespace wstest{
class SaveDelete : public WSTestBase {
 public:
  SaveDelete(std::string table, std::string insert_query,
             std::string update_query, std::string delete_query);

 protected:
  void connectToServer();
  void setMessageHandler();

 private:
  std::string table;
  std::string insert_query;
  std::string update_query;
  std::string delete_query;

  int id = 0;
};
}
#endif  // SaveDelete_H
