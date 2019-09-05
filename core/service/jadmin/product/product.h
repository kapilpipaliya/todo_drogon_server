#ifndef PRODUCT_H
#define PRODUCT_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class Product : public BaseServiceAbs
{
public:
    Product(JAdminContextPtr );
    json handleEvent(json event, int next, const json& args);
    json del(json event, json args) override;
private:
    void setupTable() override;
    json ins(json event, json args) override;
    json upd(json event, json args) override;

    json get_product_diamond_price_data( json event, json args);
    json get_product_cs_price_data( json event, json args);
    json get_product_category_tree_data( json event, const json& args);
    JAdminContextPtr context;
};
}
#endif // PRODUCT_H
