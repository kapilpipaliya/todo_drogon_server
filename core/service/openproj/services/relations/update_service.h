n#pragma once
amespace openproject {
class Relations::UpdateService : public Relations::BaseService {
  // attr_accessor :relation

   UpdateService(user:, relation:) {
    super(user: user)
    this->relation = relation
    this->contract_class = Relations::UpdateContract
  }

   void call(attributes: {}, send_notifications: true) {
    in_context(send_notifications) {
      update_relation relation, attributes
    }
  }
}
