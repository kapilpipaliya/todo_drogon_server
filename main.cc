#include <drogon/drogon.h>
#include <boost/locale.hpp>

#include "core/dgraph/dgraphclient.h"
#include "core/dgraph/dgraphclientmanger.h"
#include "core/dgraph/dgraphclientstub.h"
#include "core/dgraph/http/HttpClientManger.h"
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
  dgraph::HttpClientManager::createClient("1", "localhost", "8080", "");

  dgraph::DGraphClientStub clientStub("localhost:9080");
  auto db = dgraph::DGraphClientManger::createDGraphClient("1", clientStub);
  db.get()->debugMode = true;

  // drogon::app().addListener("0.0.0.0",8300);
  drogon::app().loadConfigFile("./config.json").run();
  std::cout.flush();
  return 0;
}
