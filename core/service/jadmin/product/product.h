#ifndef PRODUCT_H
#define PRODUCT_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
typedef std::shared_ptr<JAdminContext> JAdminContextPtr;
namespace jadmin {
class Product : public BaseServiceAbs
{
public:
    Product(const JAdminContextPtr &);
    json handleEvent(json event, int next, json args);
    json del(json event, json args);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);

    json get_product_diamond_price_data( json event, json args);
    json get_product_cs_price_data( json event, json args);
    json get_product_category_tree_data( json event, json args);
    JAdminContextPtr context;
};
}
#endif // PRODUCT_H
