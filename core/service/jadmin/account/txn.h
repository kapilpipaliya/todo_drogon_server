#ifndef TXN_H
#define TXN_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "../../baseserviceabs.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class Txn : public BaseServiceAbs {
 public:
  Txn(JAdminContextPtr);

 private:
  void setupTable() override;
  json ins(json event, json args) override;
  json upd(json event, json args) override;
  json del(json event, json args) override;
  JAdminContextPtr context;
};
}  // namespace jadmin
#endif  // TXN_H
