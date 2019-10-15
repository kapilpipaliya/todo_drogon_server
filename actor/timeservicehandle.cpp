#include "timeservicehandle.h"
#include "../core/service/time/timeservicebase.h"
//--include end--
TimeServiceHandle::TimeServiceHandle() {
  // auth
  // handleService<generator::service::Generator>(in);
  // auth
}

enum service { auth_user_login };

void TimeServiceHandle::runService(
    std::shared_ptr<websocket::todo::TodoContext> contx,
    const nlohmann::json &in) {
  auto evt = in[0][0].get<int>();

  if (evt == auth_user_login) {
  }

  //  if (evt == "auth") {
  //    r = handleService<todo::service::Auth>(contx, in);
  //  } else if (evt == 1) {
  //    r = handleService<todo::service::User>(contx, in);
  //  } else
  //  if (evt == 1) {
  //    r = handleService<todo::service::UI>(contx, in);
  //  } else if (evt == 2) {
  //    r = handleService<todo::service::Seed>(contx, in);
  //  } else
  //  if (evt == 3) {
  //    todo::service::DGraphSeed t;
  //    t.handleEvent(wsConnPtr, in[0], 1, in[1]);
  //  } else {
  //    r = nlohmann::json::array();
  //  }
}
