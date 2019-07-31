#ifndef PRODUCTQUERY_H
#define PRODUCTQUERY_H

#include "core/tables/Table.h"

#include <drogon/WebSocketController.h>

using namespace drogon;

void query_product_options(Table &t);

void query_product(Table &t);

void query_category(Table &t);

void query_shipping_class(Table &t);

void query_setting_type(Table &t);

void query_certified_by(Table &t);
void query_policy(Table &t);


void get_product_attachment_data(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
void get_product_diamond_price_data(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
void get_product_cs_price_data(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);
void get_product_category_tree_data(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);


#endif // PRODUCTQUERY_H
