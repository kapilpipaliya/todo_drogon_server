#include <utility>

#include "./session.h"
#include "../../dba.h"

jadmin::Session::Session(JAdminContextPtr context_): context(std::move(context_))
{

}

void jadmin::Session::setupTable()
{

}

bool jadmin::Session::destroy(long key)
{
    if (!key) { // !key.empty()
        return false;
    }

    // Remove anything and EVERYTHING
    std::string sql = "DELETE FROM user1.session WHERE id = $1";
    auto r = Dba::write(sql, key);
    return r.affectedRows() == 1;
    //debug_event("SESSION", "Deleting Session with key:" . key, 6);

    //session_name  = AmpConfig::get("session_name");
    //cookie_path   = AmpConfig::get("cookie_path");
    //cookie_domain = null;
    //cookie_secure = AmpConfig::get("cookie_secure");

    // Destroy our cookie!
    //setcookie(session_name, null, -1, cookie_path, cookie_domain, cookie_secure);
    //setcookie(session_name . "_user", null, -1, cookie_path, cookie_domain, cookie_secure);
    //setcookie(session_name . "_lang", null, -1, cookie_path, cookie_domain, cookie_secure);

    //return true;
}
