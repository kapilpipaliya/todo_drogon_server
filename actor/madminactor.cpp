
#include "madminactor.h"
/*
#include "../wscontroller/wsfns.h"
#include "mainactortype.h"
#include "service/madmin/class/access.h"
#include "service/madmin/class/album.h"
#include "service/madmin/class/api.h"
#include "service/madmin/class/art.h"
#include "service/madmin/class/artist.h"
#include "service/madmin/class/auth.h"
#include "service/madmin/class/bookmark.h"
#include "service/madmin/class/browse.h"
#include "service/madmin/class/catalog.h"
#include "service/madmin/class/config.h"
#include "service/madmin/class/label.h"
#include "service/madmin/class/localplay.h"
#include "service/madmin/class/localplaybase.h"
#include "service/madmin/class/log.h"
#include "service/madmin/class/mailer.h"
#include "service/madmin/class/media.h"
#include "service/madmin/class/playlist.h"
#include "service/madmin/class/playlistbase.h"
#include "service/madmin/class/preference.h"
#include "service/madmin/class/privatemsg.h"
#include "service/madmin/class/random.h"
#include "service/madmin/class/rating.h"
#include "service/madmin/class/recommandation.h"
#include "service/madmin/class/registration.h"
#include "service/madmin/class/search.h"
#include "service/madmin/class/session.h"
#include "service/madmin/class/share.h"
#include "service/madmin/class/shoutbox.h"
#include "service/madmin/class/slideshow.h"
#include "service/madmin/class/song.h"
#include "service/madmin/class/songpreview.h"
#include "service/madmin/class/stats.h"
#include "service/madmin/class/tag.h"
#include "service/madmin/class/tmpplaylist.h"
#include "service/madmin/class/ui.h"
#include "service/madmin/class/update.h"
#include "service/madmin/class/upload.h"
#include "service/madmin/class/user.h"
#include "service/madmin/class/useractivity.h"
#include "service/madmin/class/userflag.h"
#include "service/madmin/class/vainfo.h"
#include "service/madmin/modules/catalog/cataloglocal.h"
*/

//#include "madminservices.h"
namespace superactor {
namespace musicactor {
MAdminActor::MAdminActor(caf::actor_config &cfg)
    : caf::event_based_actor(cfg) {}

caf::behavior MAdminActor::make_behavior() {
  return {
      [this](const drogon::WebSocketConnectionPtr &wsConnPtr,
             std::string message,
             const drogon::WebSocketMessageType &type) -> caf::result<void> {
        blocking_run(wsConnPtr, std::move(message), type);
        return {};
      }
      //        ,
      //      [this](superactor::system::exit_atom) -> caf::result<void> {
      //        quit();
      //        return {};
      //}
  };
}  // namespace musicactor

nlohmann::json MAdminActor::handleTextMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, const nlohmann::json &in) {
  if (!in.is_array() || !in[0].is_array() || !in[0][0].is_string()) {
    return nlohmann::json::array();
  }
  auto contx = wsConnPtr->getContext<websocket::music::MAdminContext>();
  /*
  auto evt = in[0][0].get<std::string>();
  if (evt == "auth") {
    return handleService<music::service::Auth>(contx, in);
  } else if (evt == "user" || evt == "users") {
    return handleService<music::service::User>(contx, in);
  } else if (evt == "ui") {
    return handleService<music::service::UI>(contx, in);
  } else if (evt == "catalog_local") {
    return handleService<music::service::CatalogLocal>(contx, in);
  } else if (evt == "song") {
    return handleService<music::service::Song>(contx, in);
  } else {
    return nlohmann::json::array();
  }
  */
}

nlohmann::json MAdminActor::handleBinaryMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, std::string &message) {
  nlohmann::json event;
  try {
    auto contx = wsConnPtr->getContext<websocket::music::MAdminContext>();
    long c = contx->sessionId();
    auto sqlSession =
        "SELECT event FROM music.temp_file_meta where session_id = $1";
    auto clientPtr = drogon::app().getDbClient("sce");
    auto r = clientPtr->execSqlSync(sqlSession, c);
    if (!r.empty()) {
      try {
        event = nlohmann::json::parse(r[0]["event"].c_str());
        // p.handleBinaryEvent creates new transaction.
        /*
                if (event[0] == "song") {
                  music::service::Song p{contx};
                  auto r = p.handleBinaryEvent(event, 1, message);
                  if (!r.is_null()) return r;
                }*/
      } catch (nlohmann::json::parse_error &e) {
        LOG_DEBUG << "message: {}" << e.what();
        LOG_DEBUG << "exception id: {}" << e.id;
        LOG_DEBUG << "byte position of error:" << e.byte;
        nlohmann::json j =
            std::string("cant parse json reason: ") + e.what() + event.dump();
        //       websocket::WsFns::sendJson(wsConnPtr, j);
      }
    }
  } catch (const std::exception &e) {
    LOG_DEBUG << e.what();
    nlohmann::json jresult;
    jresult[0] = event;
    jresult[1] = e.what();
    return jresult;
  }
  nlohmann::json ret;
  return ret;
}

}  // namespace musicactor
}  // namespace superactor
