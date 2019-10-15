
#include <iostream>

#include "./dgraphclientmanger.h"
#include "./example.h"
#include "./test.h"
int main(int argc, char *argv[]) {
  auto dbgrpcclient =
      dgraph::DGraphClientManger::createDGraphGrpcClient("1", "localhost:9080");
  auto dborm = dgraph::DGraphClientManger::createDGraphOrm("1", "1");

  Example a;
  a.test();
  Test t;
}
