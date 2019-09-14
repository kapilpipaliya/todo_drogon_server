#pragma once
#include "../wscontroller/wsfns.h"
#include "mainactortype.h"
#include "spdlogfix.h"

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
#include "core/service/madmin/class/label.h"
#include "core/service/madmin/class/localplay.h"
#include "core/service/madmin/class/localplaybase.h"
#include "core/service/madmin/class/log.h"
#include "core/service/madmin/class/mailer.h"
#include "core/service/madmin/class/media.h"
#include "core/service/madmin/class/playlist.h"
#include "core/service/madmin/class/playlistbase.h"
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
#include "core/service/madmin/class/user.h"
#include "core/service/madmin/class/useractivity.h"
#include "core/service/madmin/class/userflag.h"
#include "core/service/madmin/class/vainfo.h"


#include "core/service/madmin/modules/catalog/cataloglocal.h"

template <typename T>
nlohmann::json handleService(std::shared_ptr<websocket::MAdminContext> contx,
                             nlohmann::json in) {
  try {
    T p{contx};
    auto r = p.handleEvent(in[0], 1, in[1]);
    if (!r.is_null()) return r;
    return nlohmann::json::array();
  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    return nlohmann::json::array({{e.what()}});
  }
}
