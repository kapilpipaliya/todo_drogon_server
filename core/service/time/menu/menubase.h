#ifndef MENUBASE_H
#define MENUBASE_H

#include "core/dgraph/dgraphclientmanger.h"
#include "json.hpp"
#include "../../../dgraph/orm/dgraphorm.h"
#include "../../../dgraph/orm/model.h"
namespace timeservice{
class MenuBase
{
public:
    MenuBase();
    void seed_init_data();
    int get_menu_count();
    void create_menu(std::string type, std::string name, std::string path, std::string icon = "");
};
}
#endif // MENUBASE_H
