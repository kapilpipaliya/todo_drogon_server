#include "menusave.h"

delFn(node, "menu.node");

delFn(role, "menu.role");

delFn(task, "menu.task");

save_table(node, "menu.node", "name", "$1", "$2", "where id=$1", in["name"].asString());

save_table(role, "menu.role", "name", "$1", "$2", "where id=$1", in["name"].asString());

save_table(task, "menu.task", "parent_id, rank, slug, label, active, url, web_icon, description, class", "$1,$2,$3,$4,$5,$6,$7,$8,$9", "$2,$3,$4,$5,$6,$7,$8,$9,$10", "where id=$1",
            in["parent_id"].asInt(),
            in["rank"].asInt(),
            in["slug"].asString(),
            in["label"].asString(),
            in["active"].asBool(),
            in["url"].asString(),
            in["web_icon"].asString(),
            in["description"].asString(),
            in["class"].asString()
           );
