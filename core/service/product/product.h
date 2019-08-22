#ifndef PRODUCT_H
#define PRODUCT_H
#include "../baseservice.h"
class Product : public BaseService
{
public:
    Product(const WebSocketConnectionPtr& wsConnPtr);
    json handleEvent(json event, int next, json args);
    json del(json event, json args);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    json get_product_attachment_data( json event, json args);
    json get_product_diamond_price_data( json event, json args);
    json get_product_cs_price_data( json event, json args);
    json get_product_category_tree_data( json event, json args);
};
#endif // PRODUCT_H
