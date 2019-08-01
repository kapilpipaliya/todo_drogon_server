#ifndef SETTINGQUERY_H
#define SETTINGQUERY_H

#include "core/tables/Table.h"
#include <drogon/WebSocketController.h>

using namespace drogon;

void query_global_setting(Table &t);

void query_currency(Table &t);

void query_log(Table &t);

void query_support(Table &t);

void query_image_collection(Table &t);

void query_image(Table &t);
void query_payment_method(Table &t);

Json::Value get_setting_thumb_data(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
#endif // SETTINGQUERY_H
