#pragma once
#include "../../services/relations/base_service.h"
namespace openproj {
namespace service {
namespace Relations {
class UpdateService : public openproj::service::Relations::BaseService {
  // attr_accessor :relation

  //   UpdateService(user:, relation:) {
  //    super(user: user)
  //    this->relation = relation
  //    this->contract_class = Relations::UpdateContract
  //  }

  //   void call(attributes: {}, send_notifications: true) {
  //    in_context(send_notifications) {
  //      update_relation relation, attributes
  //    }
  //  }
};
}  // namespace Relations
}  // namespace openproj
}
