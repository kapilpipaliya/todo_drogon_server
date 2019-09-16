#include <drogon/drogon.h>
int main() {
  // drogon::app().addListener("0.0.0.0",8300);
  drogon::app().loadConfigFile("./config.json").run();
  return 0;
}
