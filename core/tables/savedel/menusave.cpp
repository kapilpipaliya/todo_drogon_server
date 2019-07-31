#include "menusave.h"

delFn(menu_node, "menu.menu_node");

delFn(menu_role, "menu.menu_role");

delFn(menu_task, "menu.menu_task");

save_table(menu_node, "account.menu_node", "name", "$1", "$2", "where id=$1", in["name"].asString());

save_table(menu_role, "account.menu_role", "name", "$1", "$2", "where id=$1", in["name"].asString());

save_table(menu_task, "account.menu_task", "name", "$1", "$2", "where id=$1", in["name"].asString());
