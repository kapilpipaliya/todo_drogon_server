#ifndef PRODUCT_H
#define PRODUCT_H
#include "../baseservice.h"
class Product : public BaseService
{
public:
    Product(const WebSocketConnectionPtr& wsConnPtr);
    Json::Value handleEvent(Json::Value event, Json::Value args);
    Json::Value del(Json::Value event, Json::Value args);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
    Json::Value get_product_attachment_data( Json::Value event, Json::Value args);
    Json::Value get_product_diamond_price_data( Json::Value event, Json::Value args);
    Json::Value get_product_cs_price_data( Json::Value event, Json::Value args);
    Json::Value get_product_category_tree_data( Json::Value event, Json::Value args);
};
#endif // PRODUCT_H
