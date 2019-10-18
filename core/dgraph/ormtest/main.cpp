
#include <iostream>

#include "./dgraphclientmanger.h"
#include "./example.h"
#include "./test.h"
#include "core/dgraph/orm/dgraphormstartup.h"

int main(int argc, char *argv[]) {
  auto dbgrpcclient =
      dgraph::DGraphClientManger::createDGraphGrpcClient("1", "localhost:9080");
  auto dborm = dgraph::DGraphClientManger::createDGraphOrm("1", "1");

  // This creates its own schema so it now not useful:
  // Example a;
  // a.test();

  dgraph::orm::DGraphOrmStartup
      dormStartup;  // register all schema on constructor

  Test t;
}
