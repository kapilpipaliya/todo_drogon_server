#pragma once
#include "auth_sources_controller.h"
namespace openproj {
namespace controller {
class LdapAuthSourcesController : public AuthSourcesController {
public:
  // menu_item :ldap_authentication

  protected:

   void auth_source_class() {
//    LdapAuthSource
  }
};
}
}
