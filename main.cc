#include <drogon/drogon.h>
#include <boost/locale.hpp>

#include "core/dgraph/dgraphclient.h"
#include "core/dgraph/dgraphclientmanger.h"
#include "core/dgraph/dgraphclientstub.h"
#include "core/dgraph/http/HttpClientManger.h"

#include <fplus/fplus.hpp>
#include <iostream>

#include <amqpcpp.h>
#include "thirdparty/gcc_poison.h"

#include <iostream>
#include "thirdparty/kangaru.h"

//#include "mainwindow.h"
#include <QApplication>

#include "gui/mainhighscriptide.h"

#include <iostream>
#include <string>

#include <tao/pegtl.hpp>

namespace pegtl = tao::pegtl;

namespace hello {
// Parsing rule that matches a literal "Hello, ".

struct prefix : pegtl::string<'H', 'e', 'l', 'l', 'o', ',', ' '> {};

// Parsing rule that matches a non-empty sequence of
// alphabetic ascii-characters with greedy-matching.

struct name : pegtl::plus<pegtl::alpha> {};

// Parsing rule that matches a sequence of the 'prefix'
// rule, the 'name' rule, a literal "!", and 'eof'
// (end-of-file/input), and that throws an exception
// on failure.

struct grammar : pegtl::must<prefix, name, pegtl::one<'!'>, pegtl::eof> {};

// Class template for user-defined actions that does
// nothing by default.

template <typename Rule>
struct action {};

// Specialisation of the user-defined action to do
// something when the 'name' rule succeeds; is called
// with the portion of the input that matched the rule.

template <>
struct action<name> {
  template <typename Input>
  static void apply(const Input &in, std::string &v) {
    v = in.string();
  }
};

}  // namespace hello
//#include
/**
 * This example refect snippets of code found in the documentation section 1:
 * Services It explains how to branch containers and operate between them.
 */

// Camera is a user class.
struct Camera {
  int position;
};

// Scene too. User class.
struct Scene {
  Scene(Camera c, int w = 800, int h = 600)
      : camera{c.position}, width{w}, height{h} {}

 private:
  Camera camera;
  int width;
  int height;
};

struct Screen {
  Scene &scene;
  Camera camera;
};

// This is our service definitions
struct CameraService : kgr::service<Camera> {};

// SceneService is a single service of Scene, that depends on a camera
struct SceneService
    : kgr::single_service<Scene, kgr::dependency<CameraService>> {};

// ScreenService is a single service of Screen, that depends on a scene and
// camera
struct ScreenService
    : kgr::service<Screen, kgr::dependency<SceneService, CameraService>> {};

int qInit() {
  // https://stackoverflow.com/questions/1519885/defining-own-main-functions-arguments-argc-and-argv
  char *argv[] = {"program name", "arg1", "arg2", nullptr};
  int argc = sizeof(argv) / sizeof(char *) - 1;
  QApplication a(argc, argv);
  MainHighScriptIDe w;
  w.show();
  return a.exec();
}

int main(int argc, char *argv[]) {
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
  std::string name;
  if (argc > 1) {
    pegtl::argv_input in(argv, 1);
    pegtl::parse<hello::grammar, hello::action>(in, name);
    std::cout << "Good bye, " << name << "!" << std::endl;
  }
  // This is great library:
  //  https://github.com/Dobiasd/FunctionalPlus
  std::list<std::string> things = {"same old", "same old"};
  if (fplus::all_the_same(things))
    std::cout << "All things being equal." << std::endl;
  //----------------kgr-----------------------
  kgr::container container;

  // We create two cameras.
  Camera camera = container.service<CameraService>();
  Camera furtherCamera = container.service<CameraService>(14);

  // prints 0
  std::cout << "Camera Position: " << camera.position << '\n';

  // prints 14
  std::cout << "Further Camera Position: " << furtherCamera.position << '\n';

  // A Screen has a Scene and a Camera injected in it.
  Screen screen1 = container.service<ScreenService>();
  Screen screen2 = container.service<ScreenService>();

  // Spoiler: yes they are the same
  std::cout << "Is both scene the same? "
            << (&screen1.scene == &screen2.scene ? "yes" : "no") << '\n';
  std::cout.flush();
  //---------------end-----------------

  //---------qt------------------
  //  https://stackoverflow.com/questions/22289423/how-to-avoid-qt-app-exec-blocking-main-thread
  std::thread my_thread(qInit);

  //-----------end-----------
  dgraph::HttpClientManager::createClient("1", "localhost", "8080", "");

  dgraph::DGraphClientStub clientStub("localhost:9080");
  auto db = dgraph::DGraphClientManger::createDGraphClient("1", clientStub);
  db.get()->debugMode = true;

  // drogon::app().addListener("0.0.0.0",8300);
  drogon::app().loadConfigFile("./config.json").run();
  std::cout.flush();
  return 0;
}
