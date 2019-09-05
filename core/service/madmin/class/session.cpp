#include "./session.h"
#include "../../dba.h"

madmin::Session::Session(const MAdminContextPtr &context_): context(context_)
{

}

void madmin::Session::setupTable()
{

}

bool madmin::Session::destroy(long key)
{
    if (!key) { // !key.empty()
        return false;
    }

    // Remove anything and EVERYTHING
    std::string sql = "DELETE FROM music.session WHERE id = $1";
    auto r = Dba::write(sql, key);
    if(r.affectedRows() == 1){ return true; } else { return false;}

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
