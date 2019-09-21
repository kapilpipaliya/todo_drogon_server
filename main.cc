#include <drogon/drogon.h>
#include <boost/locale.hpp>
int main() {
  /*
boost::locale::generator gen;
// Specify location of dictionaries
gen.add_messages_path(".");
gen.add_messages_domain("hello");
// Generate locales and imbue them to iostream
std::locale::global(gen(""));
std::cout.imbue(std::locale());
// Display a message using current system locale
std::cout << boost::locale::translate("Hello World") << std::endl;
*/
  // drogon::app().addListener("0.0.0.0",8300);
  drogon::app().loadConfigFile("./config.json").run();
  std::cout.flush();
  return 0;
}
