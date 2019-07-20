#ifndef SAVEFUNCTIONS_H
#define SAVEFUNCTIONS_H

#include <json/json.h>
#include <drogon/WebSocketController.h>
using namespace drogon;

void printJson(Json::Value & in);
void simpleJsonResult(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, bool ok, const std::string & error);
void sendAJson(const WebSocketConnectionPtr& wsConnPtr, Json::Value out);
void saveImageMeta(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in);

#define saveDel(s)\
    void save_##s(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in);\
    void delete_##s(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in);\

// Public
// Branch
// Menu
// Mfg
// Payroll
// Material

saveDel(metal);
saveDel(purity);
saveDel(tone);
saveDel(accessory);

saveDel(clarity);
saveDel(shape);
saveDel(d_color);
saveDel(cs_color);
saveDel(diamond_size);
saveDel(color_stone_size);
// Account
// Entity
saveDel(address_type);
saveDel(contact_type);
saveDel(entity_type);
saveDel(entity);
// Setting
// Part
// product:
saveDel(category);
saveDel(product);
saveDel(post);

saveDel(tag);
saveDel(shipping_class);
saveDel(setting_type);
saveDel(certified_by);

saveDel(currency);


void get_product_attachment(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in);
void get_diamond_price(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in);
void get_cs_price(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in);
void get_product_category_tree_data(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in);


void save_product_attachment(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, std::string &message);
void admin_login(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in);
void admin_logout(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in);
void is_admin_auth(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in);


#endif // SAVEFUNCTIONS_H
