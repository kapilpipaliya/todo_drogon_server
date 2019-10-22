#ifndef MENUBASE_H
#define MENUBASE_H

#include "../../../dgraph/orm/dgraphorm.h"
#include "../../../dgraph/orm/model.h"
#include "dgraph/dgraphclientmanger.h"
#include "json.hpp"
namespace timeservice {
class MenuBase {
 public:
  MenuBase();
  void seed_init_data();
  int get_menu_count();
  void create_menu(dgraph::orm::Attributes &attributes);
};
}  // namespace timeservice
#endif  // MENUBASE_H
