#ifndef PRODUCT_H
#define PRODUCT_H

#include "core/Table.h"
#include <json/json.h>
#include "../../macro.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class Product
{
public:
    Product(const WebSocketConnectionPtr& wsConnPtr);

    HANDLEEVENTD()

private:
    void setupTable();
    HEADERDATAD()
    ALLDATAD()
    SAVED()
    DELETED()

    Table t;
    const WebSocketConnectionPtr& wsConnPtr;

    Json::Value get_product_attachment_data( Json::Value event, Json::Value args);
    Json::Value get_product_diamond_price_data( Json::Value event, Json::Value args);
    Json::Value get_product_cs_price_data( Json::Value event, Json::Value args);
    Json::Value get_product_category_tree_data( Json::Value event, Json::Value args);

};





#endif // PRODUCT_H
