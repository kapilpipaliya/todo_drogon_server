#include "./test.h"

#include "../dgraph-js/generated/api.grpc.pb.h"
#include "../dgraph-js/generated/api.pb.h"
#include "../orm/dgraphorm.h"
#include "../orm/model.h"
#include "../orm/schema.h"
#include "./dgraphclientmanger.h"

using namespace dgraph::orm;
Test::Test() {
  auto dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");

  auto user = dgraphorm->newmodel("user");
}
