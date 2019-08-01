#ifndef SETTINGSAVE_H
#define SETTINGSAVE_H

#include "../macro.h"
#include <drogon/WebSocketController.h>

using namespace drogon;

#include "core/connection/pdb.h"
#include "../jsonfns.h"
#include "../../strfns.h"
#include "core/sql/query.h"


saveDel(global_setting);

saveDel(currency);

saveDel(log);

saveDel(support);

saveDel(image_collection);

saveDel(image);
saveDel(payment_method);

Json::Value saveImageMeta(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);

//Binary functin:
Json::Value save_setting_attachment(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, std::string &message);


#endif // SETTINGSAVE_H
