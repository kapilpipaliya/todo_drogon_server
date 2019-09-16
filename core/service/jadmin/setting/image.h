#ifndef IMAGE_H
#define IMAGE_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "core/sql/query.h"

namespace jewel {
namespace service {
class Image {
 public:
  Image(std::shared_ptr<websocket::jewel::JAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, int next,
                             const nlohmann::json& args);

 private:
  void setupTable();
  nlohmann::json ins(nlohmann::json event, nlohmann::json args);
  nlohmann::json upd(nlohmann::json event, nlohmann::json args);
  std::shared_ptr<websocket::jewel::JAdminContext> context;
  sql::Query query;
};
}  // namespace service
}  // namespace jadmin
#endif  // IMAGE_H
