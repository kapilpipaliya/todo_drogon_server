#include "madminactor.h"
#include "spdlogfix.h"
#include "mainactortype.h"
#include "../wscontroller/wsfns.h"

#include "../wscontroller/context/madmincontext.h"

#include "core/service/madmin/class/access.h"
#include "core/service/madmin/class/album.h"
#include "core/service/madmin/class/api.h"
#include "core/service/madmin/class/art.h"
#include "core/service/madmin/class/artist.h"
#include "core/service/madmin/class/auth.h"
#include "core/service/madmin/class/bookmark.h"
#include "core/service/madmin/class/browse.h"
#include "core/service/madmin/class/catalog.h"
#include "core/service/madmin/class/config.h"
#include "core/service/madmin/class/dba.h"
#include "core/service/madmin/class/label.h"
#include "core/service/madmin/class/localplaybase.h"
#include "core/service/madmin/class/localplay.h"
#include "core/service/madmin/class/log.h"
#include "core/service/madmin/class/mailer.h"
#include "core/service/madmin/class/media.h"
#include "core/service/madmin/class/playlistbase.h"
#include "core/service/madmin/class/playlist.h"
#include "core/service/madmin/class/preference.h"
#include "core/service/madmin/class/privatemsg.h"
#include "core/service/madmin/class/random.h"
#include "core/service/madmin/class/rating.h"
#include "core/service/madmin/class/recommandation.h"
#include "core/service/madmin/class/registration.h"
#include "core/service/madmin/class/search.h"
#include "core/service/madmin/class/session.h"
#include "core/service/madmin/class/share.h"
#include "core/service/madmin/class/shoutbox.h"
#include "core/service/madmin/class/slideshow.h"
#include "core/service/madmin/class/song.h"
#include "core/service/madmin/class/songpreview.h"
#include "core/service/madmin/class/stats.h"
#include "core/service/madmin/class/tag.h"
#include "core/service/madmin/class/tmpplaylist.h"
#include "core/service/madmin/class/ui.h"
#include "core/service/madmin/class/update.h"
#include "core/service/madmin/class/upload.h"
#include "core/service/madmin/class/useractivity.h"
#include "core/service/madmin/class/userflag.h"
#include "core/service/madmin/class/user.h"
#include "core/service/madmin/class/vainfo.h"

#include "core/service/madmin/modules/catalog/cataloglocal.h"



MAdminActor::MAdminActor(caf::actor_config &cfg) : caf::event_based_actor(cfg)
{

}

caf::behavior MAdminActor::make_behavior()
{
    return  {
        [this](const WebSocketConnectionPtr &wsConnPtr, std::string message, const WebSocketMessageType &type)-> caf::result<void>{
            blocking_run(wsConnPtr, std::move(message), type);
            return {};
        },
        [this](exit_atom)-> caf::result<void>{
            quit();
            return {};
        }
    };
}

void MAdminActor::blocking_run(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    switch (type) {
    case WebSocketMessageType::Text: {
        try
        {
            auto valin = json::parse(message);
            if (valin.is_array()){
                json out(json::array());
                for (auto i : valin) {
                    // printJson(valin);
                    auto result  = handleTextMessage(wsConnPtr, std::move(message), i);
                    for (auto &i : result) {
                        if(!i.is_null()){
                            out.push_back(i);
                        }
                    }
                }
                if(!out.empty()){
                    WsFns::sendJson(wsConnPtr, out);
                } else {
                    nlohmann::json j =  "Message cant served: maybe not valid events in batch: " + message;
                    WsFns::sendJson(wsConnPtr, j);
                }
            } else {
                nlohmann::json j =  "Invalid Message only array handled: " + message;
                WsFns::sendJson(wsConnPtr, j);
            }
        }
        catch (json::parse_error& e)
        {
           SPDLOG_TRACE("message: {}", e.what());
           SPDLOG_TRACE("exception id: {}", e.id);
           SPDLOG_TRACE("byte position of error:", e.byte);
            nlohmann::json j =  std::string("cant parse json reason: ") + e.what() ;
            WsFns::sendJson(wsConnPtr, j);
        }
        break;
    }
    case WebSocketMessageType::Binary: {
        auto result  = handleBinaryMessage(wsConnPtr, message);
        if(!result.is_null()){
            WsFns::sendJson(wsConnPtr, result);
        }
        break;
    }
    default:
        break;
    }
}
#define REGISTER(T, s)\
    else if (in[0][0].get<std::string>()==s){\
    auto contx = wsConnPtr->getContext<MAdminContext>();\
    T p{contx};\
    auto r = p.handleEvent(in[0], 1, in[1]);\
    if(!r.is_null())\
    return r;\
    }
nlohmann::json MAdminActor::handleTextMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, nlohmann::json in)
{
    try {
        if (!in.is_array()) {
            return json::array();
        }

        if constexpr (false){
        }
        REGISTER(madmin::Auth, "auth")
        REGISTER(madmin::User, "user")
        REGISTER(madmin::User, "users")
        REGISTER(madmin::UI, "ui")
        REGISTER(madmin::CatalogLocal, "catalog_local")
        REGISTER(madmin::Song, "song")
        else {
            return json::array();
        }
        return json::array();
    } catch (const std::exception &e) {
        SPDLOG_TRACE(e.what());
        throw;
    }
}

nlohmann::json MAdminActor::handleBinaryMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &message)
{

}
