#ifndef PRODUCT_H
#define PRODUCT_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "core/sql/query.h"

namespace jadmin {
class Product {
 public:
  Product(std::shared_ptr<JAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  nlohmann::json del(nlohmann::json event, nlohmann::json args);

 private:
  void setupTable();
  nlohmann::json ins(nlohmann::json event, nlohmann::json args);
  nlohmann::json upd(nlohmann::json event, nlohmann::json args);

  nlohmann::json get_product_diamond_price_data(nlohmann::json event,
                                                nlohmann::json args);
  nlohmann::json get_product_cs_price_data(nlohmann::json event,
                                           nlohmann::json args);
  nlohmann::json get_product_category_tree_data(nlohmann::json event,
                                                const nlohmann::json& args);
  std::shared_ptr<JAdminContext> context;
  sqlb::Query query;
};
}  // namespace jadmin
#endif  // PRODUCT_H
